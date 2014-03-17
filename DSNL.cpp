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

DSNL::DSNL(QNetworkAccessManager* nam)
    : config(new DSNLConfig(nam,UrlConfig)), data(new DSNLData(nam,UrlData))
{
    QObject::connect(config,SIGNAL(completed()),this,SLOT(completedConfig()));
    QObject::connect(config,SIGNAL(failed()),this,SLOT(failedConfig()));
    QObject::connect(data,SIGNAL(completed()),this,SLOT(completedData()));
    QObject::connect(data,SIGNAL(failed()),this,SLOT(failedData()));
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
