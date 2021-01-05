QT       += core gui sql printsupport multimedia  texttospeech

QT += charts serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    cadastre.cpp \
    citoyens.cpp \
    connection.cpp \
    decaissement.cpp \
    deces.cpp \
    demandes.cpp \
    email.cpp \
    employe.cpp \
    encaissement.cpp \
    equipement.cpp \
    formation.cpp \
    main.cpp \
    mainwindow.cpp \
    naissance.cpp \
    rec.cpp \
    ressources_humaines.cpp \
    smtp.cpp \
    stat2.cpp \
    statistique.cpp \
    vehicule.cpp

HEADERS += \
    arduino.h \
    cadastre.h \
    citoyens.h \
    connection.h \
    decaissement.h \
    deces.h \
    demandes.h \
    email.h \
    employe.h \
    encaissement.h \
    equipement.h \
    formation.h \
    mainwindow.h \
    naissance.h \
    rec.h \
    ressources_humaines.h \
    smtp.h \
    stat2.h \
    state.h \
    statistique.h \
    vehicule.h

FORMS += \
    email.ui \
    mainwindow.ui \
    ressources_humaines.ui \
    stat2.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
