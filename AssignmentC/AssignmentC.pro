#-------------------------------------------------
#
# Project created by QtCreator 2013-12-08T22:49:34
#
#-------------------------------------------------

QT       += core gui sql
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AssignmentC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myitem.cpp \
    collection.cpp \
    item.cpp \
    borrower.cpp \
    datamodel.cpp \
    dataconnect.cpp \
    collectiongui.cpp \
    mofunction.cpp \
    model.cpp \
    functiongui.cpp \
    mainoperation.cpp \
    myimageitem.cpp \
    mainmenu.cpp \
    chooseborr.cpp \
    chooseitem.cpp \
    pdf.cpp

HEADERS  += mainwindow.h \
    myitem.h \
    collection.h \
    item.h \
    borrower.h \
    datamodel.h \
    dataconnect.h \
    collectiongui.h \
    mofunction.h \
    model.h \
    functiongui.h \
    mainoperation.h \
    myimageitem.h \
    mainmenu.h \
    chooseborr.h \
    chooseitem.h \
    pdf.h

FORMS    += mainwindow.ui \
    collectiongui.ui \
    functiongui.ui \
    mainoperation.ui \
    mainmenu.ui \
    chooseborr.ui \
    chooseitem.ui

RESOURCES += \
    images.qrc
