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

#include "DSNLConfig.h"

#include <QDebug>
#include <QDomElement>
#include <QDomNodeList>

DSNLConfig::DSNLConfig(HTTPStreamClient* nam, const QUrl& src, QObject* p)
    : DSNLXml(nam,src,p)
{
}
DSNLConfig::~DSNLConfig()
{
    clear();
}
void DSNLConfig::clear(){
    {
        QMap<QString,DSNLConfigSite*>::iterator it = sites.begin();
        QMap<QString,DSNLConfigSite*>::iterator end = sites.end();
        while (it != end){
            DSNLConfigSite* site = it.value();
            it = this->sites.erase(it);
            delete site;
        }
    }
    {
        QMap<QString,DSNLConfigDish*>::iterator it = dishes.begin();
        QMap<QString,DSNLConfigDish*>::iterator end = dishes.end();
        while (it != end){
            DSNLConfigDish* dish = it.value();
            it = this->dishes.erase(it);
            delete dish;
        }
    }
    {
        QMap<QString,DSNLConfigSpacecraft*>::iterator it = spacecraft.begin();
        QMap<QString,DSNLConfigSpacecraft*>::iterator end = spacecraft.end();
        while (it != end){
            DSNLConfigSpacecraft* spacecraft = it.value();
            it = this->spacecraft.erase(it);
            delete spacecraft;
        }
    }
}
void DSNLConfig::print(QTextStream& out){
    {
        QMap<QString,DSNLConfigSite*>::iterator it = sites.begin();
        QMap<QString,DSNLConfigSite*>::iterator end = sites.end();
        while (it != end){
            DSNLConfigSite* site = it.value();

            site->print(out);
            it++;
        }
    }
    {
        QMap<QString,DSNLConfigDish*>::iterator it = dishes.begin();
        QMap<QString,DSNLConfigDish*>::iterator end = dishes.end();
        while (it != end){
            DSNLConfigDish* dish = it.value();

            dish->print(out);
            it++;
        }
    }
    {
        QMap<QString,DSNLConfigSpacecraft*>::iterator it = spacecraft.begin();
        QMap<QString,DSNLConfigSpacecraft*>::iterator end = spacecraft.end();
        while (it != end){
            DSNLConfigSpacecraft* spacecraft = it.value();

            spacecraft->print(out);
            it++;
        }
    }
}
void DSNLConfig::read(){

    QDomElement el_config = dom.documentElement();
    if (!el_config.isNull()){

        clear();

        QDomNodeList sites = el_config.firstChild().childNodes();
        {
            const uint sites_len = sites.length();
            uint sites_idx;
            for (sites_idx = 0; sites_idx < sites_len; sites_idx++){
                QDomElement el_site = sites.item(sites_idx).toElement();

                DSNLConfigSite* site = new DSNLConfigSite(el_site.attribute("name"),el_site.attribute("friendlyName"),el_site.attribute("flag"));

                this->sites[site->system] = site;

                qDebug() << "config site " << site->system;

                QDomNodeList dishes = el_site.childNodes();
                const uint dishes_len = dishes.length();
                uint dishes_idx;
                for (dishes_idx = 0; dishes_idx < dishes_len; dishes_idx++){
                    QDomElement el_dish = dishes.item(dishes_idx).toElement();

                    DSNLConfigDish* dish = new DSNLConfigDish(site->system,el_dish.attribute("name"),el_dish.attribute("friendlyName"),el_dish.attribute("type"));

                    this->dishes[dish->system] = dish;

                    site->dishes[dish->system] = dish;

                    qDebug() << "config site " << site->system << ", dish " << dish->system;
                }
            }
        }
        QDomNodeList spacecraft = el_config.lastChild().childNodes();
        {
            const uint spacecraft_len = spacecraft.length();
            uint spacecraft_idx;
            for (spacecraft_idx = 0; spacecraft_idx < spacecraft_len; spacecraft_idx++){
                QDomElement el_sc = spacecraft.item(spacecraft_idx).toElement();

                DSNLConfigSpacecraft* sc = new DSNLConfigSpacecraft(el_sc.attribute("name"),el_sc.attribute("friendlyName"));

                this->spacecraft[sc->system] = sc;

                qDebug() << "config spacecraft " << sc->system;
            }
        }
    }
}
