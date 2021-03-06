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
#include <iostream>
#include <QTextStream>
#include <QTimer>

#include "Main.h"


Main::Main(int argc, char** argv)
    : QCoreApplication(argc,argv), httpc(new HTTPStreamClient(this)), dsnl(new DSNL(httpc))
{
}
Main::~Main(){

    if (0 != dsnl){
        dsnl->deleteLater();
        dsnl = 0;
    }
    if (0 != httpc){
        httpc->deleteLater();
        httpc = 0;
    }
}


int main(int argc, char** argv){

    Main main(argc,argv);

    main.dsnl->initp();

    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),main.dsnl,SLOT(updatep()));
    timer->setInterval(5000);
    timer->start();

    return main.exec();
}
