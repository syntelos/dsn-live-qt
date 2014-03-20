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
#ifndef _DSNL_DSNLXml_H
#define _DSNL_DSNLXml_H

#include <QDomDocument>
#include <QObject>
#include "HTTPStreamClient.h"
#include "HTTPStreamRequest.h"
#include "HTTPStreamResponse.h"

#include <QUrl>

/*!
 * 
 */
class DSNLXml : public QObject {
    Q_OBJECT;

    HTTPStreamClient* httpc;

 protected:

    const QUrl& src;

    HTTPStreamRequest q;

    HTTPStreamResponse p;

    QDomDocument dom;

 public:
    DSNLXml(HTTPStreamClient*, const QUrl&, QObject* p = 0);
    ~DSNLXml();

    void io();

    virtual void read() = 0;

 public slots:
    void update();

 signals:
    void completed();
    void failed();
};
#endif
