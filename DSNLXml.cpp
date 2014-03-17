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
#include <QDebug>

#include "DSNLXml.h"

DSNLXml::DSNLXml(QNetworkAccessManager* nam, const QUrl& src, QObject* p)
    : QObject(p), nam(nam), src(src), response(0), dom(0)
{
}
DSNLXml::~DSNLXml()
{
    if (0 != dom){
        delete dom;
        dom = 0;
    }
    if (0 != response){
        delete response;
        response = 0;
    }
}
void DSNLXml::update(){
    if (0 != response){
        delete response;
    }
    qDebug() << "update";

    QNetworkRequest q(src);
    q.setRawHeader("User-Agent","Syntelos-DSN-Live/1.0");

    response = nam->get(q);
    QObject::connect(response,SIGNAL(readyRead()),this,SLOT(read()));
    QObject::connect(response,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));
}
void DSNLXml::read(){
    if (0 != dom){
        delete dom;
    }
    qDebug() << "read <begin>";

    dom = new QDomDocument();
    dom->setContent(response,true);

    readDom();

    qDebug() << "read <end>";

    response->close();

    delete dom;
    dom = 0;

    response->deleteLater();
    response = 0;
}
void DSNLXml::error(QNetworkReply::NetworkError code){

    switch(code){
    case QNetworkReply::NoError:
        qDebug() << "error: none";
        break;
    case QNetworkReply::ConnectionRefusedError:
        qDebug() << "error: connection refused";
        emit failed();
        break;
    case QNetworkReply::RemoteHostClosedError:
        qDebug() << "error: remote host closed";
        emit failed();
        break;
    case QNetworkReply::HostNotFoundError:
        qDebug() << "error: host not found";
        emit failed();
        break;
    case QNetworkReply::TimeoutError:
        qDebug() << "error: timeout";
        emit failed();
        break;
    case QNetworkReply::OperationCanceledError:
        //qDebug() << "error: operation cancelled";
        break;
    case QNetworkReply::SslHandshakeFailedError:
        qDebug() << "error: ssl handshake failed";
        emit failed();
        break;
    case QNetworkReply::TemporaryNetworkFailureError:
        qDebug() << "error: temporary network failure";
        emit failed();
        break;
    case QNetworkReply::ProxyConnectionRefusedError:
        qDebug() << "error: proxy connection refused";
        emit failed();
        break;
    case QNetworkReply::ProxyConnectionClosedError:
        qDebug() << "error: proxy connection closed";
        emit failed();
        break;
    case QNetworkReply::ProxyNotFoundError:
        qDebug() << "error: proxy not found";
        emit failed();
        break;
    case QNetworkReply::ProxyTimeoutError:
        qDebug() << "error: proxy timeout";
        emit failed();
        break;
    case QNetworkReply::ProxyAuthenticationRequiredError:
        qDebug() << "error: proxy authentication required";
        emit failed();
        break;
    case QNetworkReply::ContentAccessDenied:
        qDebug() << "error: access denied";
        emit failed();
        break;
    case QNetworkReply::ContentOperationNotPermittedError:
        qDebug() << "error: operation not permitted";
        emit failed();
        break;
    case QNetworkReply::ContentNotFoundError:
        qDebug() << "error: content not found";
        emit failed();
        break;
    case QNetworkReply::AuthenticationRequiredError:
        qDebug() << "error: authentication required";
        emit failed();
        break;
    case QNetworkReply::ContentReSendError:
        qDebug() << "error: content resend";
        emit failed();
        break;
    case QNetworkReply::ProtocolUnknownError:
        qDebug() << "error: unknown";
        emit failed();
        break;
    case QNetworkReply::ProtocolInvalidOperationError:
        qDebug() << "error: invalid operation";
        emit failed();
        break;
    case QNetworkReply::UnknownNetworkError:
        qDebug() << "error: network";
        emit failed();
        break;
    case QNetworkReply::UnknownProxyError:
        qDebug() << "error: proxy";
        emit failed();
        break;
    case QNetworkReply::UnknownContentError:
        qDebug() << "error: unknown content";
        emit failed();
        break;
    case QNetworkReply::ProtocolFailure:
        qDebug() << "error: protocol failure";
        emit failed();
        break;
    default:
        qDebug() << "error: <code unknown>";
        emit failed();
        break;
    }
}
