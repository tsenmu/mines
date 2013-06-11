#-------------------------------------------------
#
# Project created by QtCreator 2013-05-02T11:38:37
#
#-------------------------------------------------

QT       += core gui xml

TARGET = mines
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    minesbutton.cpp \
    minesmodel.cpp \
    minesmodeltile.cpp \
    minescounterwidget.cpp \
    minesfieldwidget.cpp \
    mineswidget.cpp \
    minesstartwidget.cpp \
    minesspinbox.cpp \
    minesmenuwidget.cpp \
    minesachievementswidget.cpp \
    minesrankingwidget.cpp \
    minesranking.cpp \
    minesrankingitem.cpp \
    minesachievementdialog.cpp \
    minesfailuredialog.cpp

HEADERS  += mainwindow.h \
    minesbutton.h \
    minesmodel.h \
    minesmodeltile.h \
    minescounterwidget.h \
    minesfieldwidget.h \
    mineswidget.h \
    minesstartwidget.h \
    minesspinbox.h \
    minesmenuwidget.h \
    minesachievementswidget.h \
    minesrankingwidget.h \
    minesranking.h \
    minesrankingitem.h \
    minesachievementdialog.h \
    minesfailuredialog.h

FORMS    += mainwindow.ui \
    minescounterwidget.ui \
    mineswidget.ui \
    minesstartwidget.ui \
    minesspinbox.ui \
    minesmenuwidget.ui \
    minesachievementswidget.ui \
    minesachievementdialog.ui \
    minesfailuredialog.ui

RESOURCES += \
    img.qrc
