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
#ifndef _DSNL_DSNLData_H
#define _DSNL_DSNLData_H

#include "DSNLXml.h"
#include <QList>
#include <QTextStream>

#include "DSNLDataStation.h"

/*!
 * 
 */
class DSNLData : public DSNLXml {
    Q_OBJECT;

 public:

    QDateTime timestamp;

    QList<DSNLDataStation*> stations;

    DSNLData(HTTPStreamClient*, const QUrl&, QObject* p = 0);
    ~DSNLData();

    void clear();

    void print(QTextStream&);

    virtual void read();

 protected:
    virtual void prepare();

};
#endif
