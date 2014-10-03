#-------------------------------------------------
#
# Project created by QtCreator 2012-08-03T22:03:40
#
#-------------------------------------------------

QT       += core gui sql network declarative printsupport

TARGET = VOM
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp \
    xabout.cpp \
    comtanscene.cpp \
    node.cpp \
    kor.cpp \
    frmrec.cpp \
    frmtab.cpp \
    mgview.cpp \
    vonal.cpp

HEADERS  += frmmain.h \
    xabout.h \
    comtanscene.h \
    node.h \
    kor.h \
    frmrec.h \
    frmtab.h \
    mgview.h \
    vonal.h

FORMS    += frmmain.ui \
    xabout.ui \
    frmrec.ui \
    frmtab.ui

RESOURCES += \
    figs.qrc
