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
#include <cmath>

#include "DSNLDataStationSignal.h"

DSNLDataStationSignal::Type DSNLDataStationSignal::TypeOf(QString string){
    if (string == "none"){
        return DSNLDataStationSignal::TypeNone;
    }
    else if (string == "carrier"){
        return DSNLDataStationSignal::TypeCarrier;
    }
    else if (string == "data"){
        return DSNLDataStationSignal::TypeData;
    }
    else {
        return DSNLDataStationSignal::TypeUnrecognized;
    }
}
double DSNLDataStationSignal::PowerOf(Direction direction, QString string){
    bool ok;
    double value = string.toDouble(&ok);
    if (ok){
        switch(direction){
        case DirectionUp:
            return value;
        case DirectionDown:
            return std::pow(10, (value - 60.0) / 10.0);
        default:
            return 0.0;
        }
    }
    else
        return 0.0;
}
DSNLDataStationSignal::DSNLDataStationSignal(Direction direction, QString type, QString rate, QString frequency,
                                             QString power, QString spacecraft)
    : direction(direction), type(TypeOf(type)), 
      dataRate(rate.toDouble()), frequency(frequency.toDouble()),
      power(PowerOf(direction,power)), spacecraft(spacecraft)
{
}
DSNLDataStationSignal::~DSNLDataStationSignal()
{
}
void DSNLDataStationSignal::print(QTextStream& out){
    out << "signal ";

    switch(direction){
    case DirectionUp:
        out << "up, ";
        break;
    case DirectionDown:
        out << "down, ";
        break;
    default:
        out << "<unknown>, ";
        break;
    }
    switch(type){
    case TypeNone:
        out << "type none, ";
        break;
    case TypeCarrier:
        out << "type carrier, ";
        break;
    case TypeData:
        out << "type data, ";
        break;
    default:
        out << "type <unknown>, ";
        break;
    }
    out << "dataRate " << dataRate << ", ";
    out << "frequency " << frequency << ", ";
    out << "power " << power << ", ";
    out << "spacecraft " << spacecraft << endl;
}
