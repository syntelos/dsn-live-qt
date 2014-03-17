TEMPLATE = app
TARGET = dsn-live
DEPENDPATH += .
INCLUDEPATH += .

QT += network
QT += xml

CONFIG += debug

HEADERS += DSNL.h \
           DSNLConfig.h \
           DSNLConfigDish.h \
           DSNLConfigSite.h \
           DSNLConfigSpacecraft.h \
           DSNLData.h \
           DSNLDataStation.h \
           DSNLDataStationDish.h \
           DSNLDataStationSignal.h \
           DSNLDataStationTarget.h \
           DSNLXml.h \
           Main.h

SOURCES += DSNL.cpp \
           DSNLConfig.cpp \
           DSNLConfigDish.cpp \
           DSNLConfigSite.cpp \
           DSNLConfigSpacecraft.cpp \
           DSNLData.cpp \
           DSNLDataStation.cpp \
           DSNLDataStationDish.cpp \
           DSNLDataStationSignal.cpp \
           DSNLDataStationTarget.cpp \
           DSNLXml.cpp \
           Main.cpp
