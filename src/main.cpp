#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

#ifdef Q_OS_WIN
//#include <QCleanlooksStyle>
//#include <QGtkStyle>
//#include <QMotifStyle>
//#include <QWindowsStyle>
//#include <QPlastiqueStyle>
//#include <QWindowsXPStyle>
//#include <QWindowsVistaStyle>
#endif

#include "frmmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale swiss("de_CH");
    #ifdef Q_OS_WIN
        //QApplication::setStyle(new QCleanlooksStyle());
    #endif
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    qtTranslator.load("qt_hu_HU", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    //qDebug() << QLocale::system().name();

    QTranslator myapp;
    myapp.load("myapp_" + QLocale::system().name());
//    myapp.load("myapp_hu_HU");
    a.installTranslator(&myapp);

    frmMain w;
    w.show();
    
    return a.exec();
}



