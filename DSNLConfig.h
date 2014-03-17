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
#ifndef _DSNL_DSNLConfig_H
#define _DSNL_DSNLConfig_H

#include "DSNLXml.h"
#include <QMap>
#include <QTextStream>

#include "DSNLConfigSite.h"
#include "DSNLConfigDish.h"
#include "DSNLConfigSpacecraft.h"

/*!
 * 
 */
class DSNLConfig : public DSNLXml {
    Q_OBJECT;

 public:

    QMap<QString,DSNLConfigSite*> sites;

    QMap<QString,DSNLConfigDish*> dishes;

    QMap<QString,DSNLConfigSpacecraft*> spacecraft;

    DSNLConfig(QNetworkAccessManager*, const QUrl&, QObject* p = 0);
    ~DSNLConfig();

    void clear();

    void print(QTextStream&);

    virtual void readDom();

};
#endif
