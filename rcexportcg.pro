#-------------------------------------------------
#
# Project created by QtCreator 2017-08-29T20:52:37
#
#-------------------------------------------------

QT       += core gui network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rcexportcg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rundowncreator.cpp \
    rundown.cpp \
    rundownrow.cpp \
    settingsdialog.cpp \
    rundownrowmodel.cpp \
    preset.cpp \
    presetstore.cpp \
    settingsmodel.cpp \
    logmodel.cpp \
    settingsdelegate.cpp \
    folder.cpp \
    groupedcombobox.cpp \
    groupedcomboboxdelegate.cpp \
    presetobjectdialog.cpp

HEADERS += \
    mainwindow.h \
    rundowncreator.h \
    rundown.h \
    rundownrow.h \
    settingsdialog.h \
    rundownrowmodel.h \
    preset.h \
    presetstore.h \
    settingsmodel.h \
    logmodel.h \
    settingsdelegate.h \
    folder.h \
    groupedcombobox.h \
    groupedcomboboxdelegate.h \
    presetobjectdialog.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    presetobjectdialog.ui

RESOURCES += \
    rcexportcg.qrc
