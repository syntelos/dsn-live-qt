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
#ifndef _DSNL_DSNLDataStationDish_H
#define _DSNL_DSNLDataStationDish_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QTextStream>

#include "DSNLDataStationSignal.h"
#include "DSNLDataStationTarget.h"

/*!
 * 
 */
class DSNLDataStationDish {

 public:
    const QString system;
    const double azimuth;
    const double elevation;
    const QDateTime created;
    const QDateTime updated;

    QList<DSNLDataStationSignal*> signal;
    QList<DSNLDataStationTarget*> target;

    DSNLDataStationDish(const QString&,const QString&,const QString&,const QString&,const QString&);
    ~DSNLDataStationDish();

    void print(QTextStream&);

};
#endif
