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
#ifndef _DSNL_DSNL_H
#define _DSNL_DSNL_H

#include "DSNLConfig.h"
#include "DSNLData.h"

#include <QTimer>

/*!
 * 
 */
class DSNL : public QObject {
    Q_OBJECT;

 public:
    const static QUrl UrlConfig;
    const static QUrl UrlData;

    DSNLConfig config;

    DSNLData data;

    DSNL(QNetworkAccessManager*);
    ~DSNL();

 public slots:
    /*
     * Fetch config and data
     */
    void init();
    /*
     * Fetch data
     */
    void update();

 signals:
    /*
     * Completed fetch of config
     */
    void completedConfig();
    /*
     * Completed fetch of data
     */
    void completedData();
    /*
     * Failed fetch of config
     */
    void failedConfig();
    /*
     * Failed fetch of data
     */
    void failedData();

};
#endif
