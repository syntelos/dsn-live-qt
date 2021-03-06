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
#ifndef _DSNL_DSNLDataStationSignal_H
#define _DSNL_DSNLDataStationSignal_H

#include <QString>
#include <QTextStream>

/*!
 * 
 */
class DSNLDataStationSignal {

 public:
    enum Direction {
        DirectionUp,
        DirectionDown
    };
    enum Type {
        TypeUnrecognized,
        TypeNone,
        TypeCarrier,
        TypeData
    };
    static Type TypeOf(const QString&);

    static double PowerOf(Direction,const QString&);

    const Direction direction;

    const Type type;

    const double dataRate; // bps

    const double frequency; // Hz

    const double power; // kW

    const QString spacecraft; // system name


    DSNLDataStationSignal(Direction,const QString&,const QString&,const QString&,const QString&,const QString&);
    ~DSNLDataStationSignal();

    void print(QTextStream&);

};
#endif
