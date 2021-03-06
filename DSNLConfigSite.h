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
#ifndef _DSNL_DSNLConfigSite_H
#define _DSNL_DSNLConfigSite_H

#include <QString>
#include <QMap>
#include <QTextStream>

#include "DSNLConfigDish.h"

/*!
 * 
 */
class DSNLConfigSite {

 public:

    const QString system;
    const QString display;
    const QString flag;

    QMap<QString,DSNLConfigDish*> dishes;

    DSNLConfigSite(const QString&,const QString&,const QString&);
    DSNLConfigSite(const DSNLConfigSite&);
    ~DSNLConfigSite();

    void clear();

    void print(QTextStream&);

};
#endif
