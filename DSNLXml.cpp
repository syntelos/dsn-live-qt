/*
 * DSN Live Qt
 * Copyright (C) 2014, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QDebug>

#include "DSNLXml.h"

DSNLXml::DSNLXml(HTTPStreamClient* httpc, const QUrl& src, QObject* p)
    : QObject(p), httpc(httpc), src(src), q(src), p(), dom()
{
    q.setHeader("User-Agent","Syntelos-DSN-Live/1.0");
}
DSNLXml::~DSNLXml()
{
}
void DSNLXml::close(){

    httpc->close();
}
void DSNLXml::update(){

    prepare();

    if (httpc->isOpen()){

        qDebug() << "DSNLXml::update <continue>";

        io();
    }
    else {
        int port = src.port();
        if (-1 == port){
            port = 80;
        }
        httpc->connectToHost(src.host(),port);

        if (httpc->waitForConnected()){

            qDebug() << "DSNLXml::update <reopen>";

            io();
        }
        else {
            emit failed();
        }
    }
}
void DSNLXml::io(){

    qDebug() << q.headline().data();

    q.write(httpc);

    p.read(httpc);

    qDebug() << p.headline().data();

    if (p.isOk()){

        // qDebug() << p.QBuffer::data() // print XML 

        dom.setContent(&p,true);

        read();
    }
    else {

        emit failed();
    }
}
