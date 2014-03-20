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
#ifndef _DSNL_DSNLDataStation_H
#define _DSNL_DSNLDataStation_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QTextStream>
#include "DSNLDataStationDish.h"

/*!
 * 
 */
class DSNLDataStation {

 public:
    const QString system;
    const QString display;
    const QDateTime timeUTC;
    const int timeZoneOffset;

    QList<DSNLDataStationDish*> dishes;

    DSNLDataStation(const QString&,const QString&,const QString&,const QString&);
    ~DSNLDataStation();

    void print(QTextStream&);

    static QDateTime ConvertTimeUTC(const QString&);
    static int ConvertTimeZoneOfs(const QString&);

};
#endif
