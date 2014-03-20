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

#include "DSNL.h"

const QUrl DSNL::UrlConfig("http://eyes.nasa.gov/dsn/config.xml");
const QUrl DSNL::UrlData("http://eyes.nasa.gov/dsn/data/dsn.xml");

DSNL::DSNL(HTTPStreamClient* httpc)
    : config(new DSNLConfig(httpc,UrlConfig)), data(new DSNLData(httpc,UrlData))
{
    QObject::connect(config,SIGNAL(completed()),this,SIGNAL(completedConfig()));
    QObject::connect(config,SIGNAL(failed()),this,SIGNAL(failedConfig()));
    QObject::connect(data,SIGNAL(completed()),this,SIGNAL(completedData()));
    QObject::connect(data,SIGNAL(failed()),this,SIGNAL(failedData()));

    /* (printing)
     */
    QObject::connect(httpc,SIGNAL(error(QAbstractSocket::SocketError)),httpc,SLOT(printSocketError(QAbstractSocket::SocketError)));
}
DSNL::~DSNL()
{
    if (0 != config){
        config->deleteLater();
        config = 0;
    }
    if (0 != data){
        data->deleteLater();
        data = 0;
    }
}
void DSNL::init()
{
    config->update();
    data->update();
}
void DSNL::update()
{
    data->update();
}
void DSNL::print(QTextStream& out){
    config->print(out);
    data->print(out);
}
