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

#include "DSNLDataStationDish.h"

DSNLDataStationDish::DSNLDataStationDish(const QString& system, const QString& az, const QString& el, 
                                         const QString& cr, const QString& up)
    : system(system), azimuth(az.toDouble()), elevation(el.toDouble()), 
      created(QDateTime::fromString(cr)), updated(QDateTime::fromString(up)),
      signal(), target()
{
}
DSNLDataStationDish::~DSNLDataStationDish()
{
    {
        QList<DSNLDataStationSignal*>::iterator it = signal.begin();
        QList<DSNLDataStationSignal*>::iterator end = signal.end();

        while (it != end){
            DSNLDataStationSignal* sig = *it;
            delete sig;

            it = signal.erase(it);
        }
    }
    {
        QList<DSNLDataStationTarget*>::iterator it = target.begin();
        QList<DSNLDataStationTarget*>::iterator end = target.end();

        while (it != end){
            DSNLDataStationTarget* tgt = *it;
            delete tgt;

            it = target.erase(it);
        }
    }
}
void DSNLDataStationDish::print(QTextStream& out){

    out << "\tdish " << system << ", az " << azimuth << ", el " << elevation << endl;
    {
        QList<DSNLDataStationSignal*>::iterator it = signal.begin();
        QList<DSNLDataStationSignal*>::iterator end = signal.end();

        while (it != end){
            DSNLDataStationSignal* sig = *it++;

            sig->print(out);
        }
    }
    {
        QList<DSNLDataStationTarget*>::iterator it = target.begin();
        QList<DSNLDataStationTarget*>::iterator end = target.end();

        while (it != end){
            DSNLDataStationTarget* tgt = *it++;

            tgt->print(out);
        }
    }
}
