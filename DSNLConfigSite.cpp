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

#include "DSNLConfigSite.h"

DSNLConfigSite::DSNLConfigSite(const QString& system, const QString& display, const QString& flag)
    : system(system), display(display), flag(flag), dishes()
{
}
DSNLConfigSite::DSNLConfigSite(const DSNLConfigSite& copy)
    : system(copy.system), display(copy.display), flag(copy.flag), dishes(copy.dishes)
{
}
DSNLConfigSite::~DSNLConfigSite()
{
    clear();
}
void DSNLConfigSite::clear(){
    QMap<QString,DSNLConfigDish*>::iterator it = dishes.begin();
    QMap<QString,DSNLConfigDish*>::iterator end = dishes.end();
    while (it != end){
        DSNLConfigDish* dish = it.value();
        it = this->dishes.erase(it);
        delete dish;
    }
}
void DSNLConfigSite::print(QTextStream& out)
{
    out << "\tsite " << system << ", '" << display << "'" << endl;
    {
        QMap<QString,DSNLConfigDish*>::iterator it = dishes.begin();
        QMap<QString,DSNLConfigDish*>::iterator end = dishes.end();
        while (it != end){
            DSNLConfigDish* dish = it.value();

            dish->print(out);
            it++;
        }
    }
}
