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

DSNLXml::DSNLXml(QNetworkAccessManager* nam, const QUrl& src, QObject* p)
    : QObject(p), nam(nam), src(src), response(0)
{
}
DSNLXml::~DSNLXml()
{
    if (0 != response){
        delete response;
        response = 0;
    }
}
void DSNLXml::update(){
    if (0 != response){
        delete response;
    }

    QNetworkRequest q(src);
    q.setRawHeader("User-Agent","Syntelos-DSN-Live/1.0");

    response = nam->get(q);
    QObject::connect(response,SIGNAL(readyRead()),this,SLOT(read()));
    QObject::connect(response,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));
}
void DSNLXml::read(){
    if (0 != dom){
        delete dom;
    }
    dom = new QDomDocument();
    dom->setContent(response,true);

    readDom();
}
void DSNLXml::error(QNetworkReply::NetworkError code){
    emit failed();
}
