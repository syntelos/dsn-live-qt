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
#include <cmath>

#include "DSNLData.h"
#include "DSNLDataStationDish.h"
#include "DSNLDataStationSignal.h"
#include "DSNLDataStationTarget.h"

DSNLData::DSNLData(HTTPStreamClient* nam, const QUrl& src, QObject* p)
    : DSNLXml(nam,src,p), stations()
{
}
DSNLData::~DSNLData()
{
    clear();
}
void DSNLData::prepare(){
    QString path = src.path();
    path += "?r=";
	
    qint64 r_value = std::floor( QDateTime::currentMSecsSinceEpoch() / 5000);
    {
        QString r_format;
        r_format = QString("%1").arg(r_value);
        path += r_format;
    }
    QVariant qv(path);

    q.path.swap(qv);
}
void DSNLData::clear(){
    QList<DSNLDataStation*>::iterator it = stations.begin();
    QList<DSNLDataStation*>::iterator end = stations.end();
    while (it != end){
        DSNLDataStation* station = *it;

        delete station;

        it = stations.erase(it);
    }
}
void DSNLData::print(QTextStream& out){

    QDateTime current = QDateTime::currentDateTime();

    out << "> current time " << current.toString() << endl;

    out << "data timestamp " << timestamp.toString() << endl;

    QList<DSNLDataStation*>::iterator it = stations.begin();
    QList<DSNLDataStation*>::iterator end = stations.end();
    while (it != end){
        DSNLDataStation* station = *it++;

        station->print(out);
    }
}
void DSNLData::read(){

    QDomElement el_dsn = dom.documentElement();
    if (!el_dsn.isNull()){

        clear();

        QDomNodeList dsn_list = el_dsn.childNodes();
        const uint dsn_list_len = dsn_list.length();
        uint dsn_list_idx;
        DSNLDataStation* station;

        for (dsn_list_idx = 0; dsn_list_idx < dsn_list_len; dsn_list_idx++){
            QDomElement el = dsn_list.item(dsn_list_idx).toElement();
            QString el_tn = el.tagName();

            if (el_tn == "station"){

                station = new DSNLDataStation(el.attribute("name"),el.attribute("friendlyName"),el.attribute("timeUTC"),el.attribute("timeZoneOffset"));
                stations.push_back(station);

                //qDebug() << "data station " << station->system;

            }
            else if (el_tn == "dish"){

                DSNLDataStationDish *dish = new DSNLDataStationDish(el.attribute("name"),el.attribute("azimuthAngle"),el.attribute("elevationAngle"),el.attribute("created"),el.attribute("updated"));

                station->dishes.push_back(dish);

                //qDebug() << "data dish " << dish->system;

                uint lidx;

                QDomNodeList list_downSignal = el.elementsByTagName("downSignal");
                const uint list_downSignal_len = list_downSignal.length();

                for (lidx = 0; lidx < list_downSignal_len; lidx++){
                    QDomElement lel = list_downSignal.item(lidx).toElement();

                    DSNLDataStationSignal* signal = new DSNLDataStationSignal(DSNLDataStationSignal::DirectionDown,
                                                                              lel.attribute("signalType"),
                                                                              lel.attribute("dataRate"),
                                                                              lel.attribute("frequency"),
                                                                              lel.attribute("power"),
                                                                              lel.attribute("spacecraft"));

                    //qDebug() << "data signal down " << signal->spacecraft;

                    dish->signal.push_back(signal);
                }

                QDomNodeList list_upSignal = el.elementsByTagName("upSignal");
                const uint list_upSignal_len = list_upSignal.length();

                for (lidx = 0; lidx < list_upSignal_len; lidx++){
                    QDomElement lel = list_upSignal.item(lidx).toElement();

                    DSNLDataStationSignal* signal = new DSNLDataStationSignal(DSNLDataStationSignal::DirectionUp,
                                                                              lel.attribute("signalType"),
                                                                              lel.attribute("dataRate"),
                                                                              lel.attribute("frequency"),
                                                                              lel.attribute("power"),
                                                                              lel.attribute("spacecraft"));

                    //qDebug() << "data signal up " << signal->spacecraft;

                    dish->signal.push_back(signal);
                }

                QDomNodeList list_targets = el.elementsByTagName("target");
                const uint list_targets_len = list_targets.length();

                for (lidx = 0; lidx < list_targets_len; lidx++){
                    QDomElement lel = list_targets.item(lidx).toElement();

                    DSNLDataStationTarget* target = new DSNLDataStationTarget(lel.attribute("name"),
                                                                              lel.attribute("uplegRange"),
                                                                              lel.attribute("downlegRange"),
                                                                              lel.attribute("rtlt"));

                    //qDebug() << "data target " << target->system;

                    dish->target.push_back(target);
                }

            }
            else if (el_tn == "timestamp"){

                QString value = el.firstChild().nodeValue();

                bool ok;
                qint64 udate = value.toLongLong(&ok);
                if (ok){

                    this->timestamp = QDateTime::fromMSecsSinceEpoch(udate);
                }
                //qDebug() << "data timestamp " << this->timestamp.toString();
            }
        }
    }
}
