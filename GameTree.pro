#-------------------------------------------------
#
# Project created by QtCreator 2019-02-06T14:43:43
#
#-------------------------------------------------

QT       += core gui sql multimedia multimediawidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameTree
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 warn_on

LIBS += -lUser32

SOURCES += \
    aviwriter.cpp \
        main.cpp \
        mainwindow.cpp \
    treemodel.cpp \
    treeitem.cpp \
    addgamedialog.cpp \
    mylineedit.cpp \
    addmoddialog.cpp \
    argsdialog.cpp \
    editmoddialog.cpp \
    myprogressbar.cpp \
    playlistform.cpp \
    myproxymodel.cpp \
    optionsdialog.cpp \
    helpdialog.cpp \
    mytreeview.cpp

HEADERS += \
    aviwriter.h \
        mainwindow.h \
    treemodel.h \
    treeitem.h \
    addgamedialog.h \
    mylineedit.h \
    addmoddialog.h \
    argsdialog.h \
    editmoddialog.h \
    myprogressbar.h \
    playlistform.h \
    myproxymodel.h \
    optionsdialog.h \
    helpdialog.h \
    mytreeview.h

FORMS += \
        mainwindow.ui \
    addgamedialog.ui \
    addmoddialog.ui \
    argsdialog.ui \
    editmoddialog.ui \
    playlistform.ui \
    optionsdialog.ui \
    helpdialog.ui

TRANSLATIONS += GameTree_ru.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GameTree_ru.ts

RESOURCES += \
    icons.qrc \
    styles.qrc \
    help.qrc

VERSION = 0.1.0.1
QMAKE_TARGET_PRODUCT = Game Tree
QMAKE_TARGET_COPYRIGHT = Zherebkov Maxim

RC_ICONS = "./icons/tree_64.ico"
