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

#include "DSNLDataStation.h"

DSNLDataStation::DSNLDataStation(const QString& system, const QString& display, const QString& utc, const QString& tzo)
    : system(system), display(display), 
      timeUTC(ConvertTimeUTC(utc)), timeZoneOffset(ConvertTimeZoneOfs(tzo)),
      dishes()
{
}
DSNLDataStation::~DSNLDataStation()
{
    QList<DSNLDataStationDish*>::iterator it = dishes.begin();
    QList<DSNLDataStationDish*>::iterator end = dishes.end();
    while (it != end){
        DSNLDataStationDish* dish = *it;

        delete dish;

        it = dishes.erase(it);
    }
}
void DSNLDataStation::print(QTextStream& out){

    out << "data station " << system << " '" << display << "', time " << timeUTC.toString() << endl;

    QList<DSNLDataStationDish*>::iterator it = dishes.begin();
    QList<DSNLDataStationDish*>::iterator end = dishes.end();
    while (it != end){
        DSNLDataStationDish* dish = *it++;

        dish->print(out);
    }
}
QDateTime DSNLDataStation::ConvertTimeUTC(const QString& string){
    bool ok;
    qint64 value = string.toLongLong(&ok);
    if (ok){
        return QDateTime::fromMSecsSinceEpoch(value);
    }
    else {
        QDateTime nil;
        return nil;
    }
}
int DSNLDataStation::ConvertTimeZoneOfs(const QString& string){
    bool ok;
    int value = string.toInt(&ok);
    if (ok){
        return value;
    }
    else {
        return 0;
    }
}
