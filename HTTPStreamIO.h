/*
 * ISS Live Qt
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
#ifndef _ISSL_HTTPStreamIO_H
#define _ISSL_HTTPStreamIO_H

#include <QBuffer>
#include <QIODevice>
#include <QList>

#include "HTTPStreamHeader.h"

namespace HTTP {
    static const char* SC = ";";
    static const char* EQ = "=";
    static const char* SP = " ";
    static const char* CRLF = "\r\n";
    /*!
     * Argument to HTTPStreamIO read and write abstracts from \class
     * QTcpSocket.
     */
    struct Device {

        virtual bool isOpen() = 0;

        virtual bool waitForReadyRead() = 0;

        virtual QByteArray readLine() = 0;

        virtual QByteArray read(qint64) = 0;

        virtual QString peerName() const = 0;

        virtual quint16 peerPort() const = 0;

        virtual void write(const QByteArray&) = 0;

        virtual void write(const char*) = 0;
    };
}

/*!
 * A \class QIODevice for HTTP entity body buffers: subclasses \class
 * HTTPStreamRequest and \class HTTPStreamResponse.
 */
struct HTTPStreamIO : public QList<HTTPStreamHeader>, public QBuffer {
    /*!
     */
    HTTPStreamIO();

    /*!
     * Prepare for reading, vacate all state
     */
    void clear();
    /*!
     * Check unique item in list by name
     */
    bool hasHeader(const QVariant& name);
    /*!
     * Check unique item in list by name
     */
    bool hasNotHeader(const QVariant& name);
    /*!
     * Set unique item in list by name
     */
    void setHeader(const QVariant& name, const QVariant& value);
    /*!
     * Fetch item from list by name
     */
    const QVariant& getHeader(const QVariant& name) const;
    /*!
     * Header convenience
     */
    void setContentLength(uint len);
    /*!
     * Header convenience
     */
    uint getContentLength() const;
    /*!
     * Header convenience
     */
    void setContentType(const QVariant& string);
    /*!
     * Header convenience
     */
    QString getContentType() const;
    /*!
     * Request or response line
     */
    virtual QByteArray headline() = 0;
    /*!
     * Whether content of this data structure forms a valid HTTP
     * entity
     */
    virtual bool isValid() = 0;
    /*!
     * Read the content of this data structure
     */
    virtual void read(HTTP::Device* io) = 0;
    /*!
     * Write the content of this data structure
     */
    virtual void write(HTTP::Device* io) = 0;

 protected:
    void readTail(HTTP::Device* io);
    void writeTail(HTTP::Device* io);
};
#endif
