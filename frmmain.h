#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QSqlDatabase>
//#include <QGraphicsScene>
#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QToolButton>

#include "mgview.h"
#include "comtanscene.h"

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();
    Ui::frmMain *ui;
    mGview *gView;
    QSqlDatabase db;
    comtanScene *scene;
    QString rtgFile;
    QString pid;
    double z;
    QComboBox* fureszek;
    QDoubleSpinBox* mertek;
    QToolButton* tbpan;
    QToolButton* tbpointer;
    QToolButton* tbpont;
    QComboBox *cb;
    QSpinBox *betu;


protected:
    void changeEvent(QEvent *e);

private slots:
    void nevjegy();
    void loadRTG();
    void addRTGtoDB();
    void editRTGtoDB();
    void saveRTGtoDB();
    void listDB();
    void iZoom(const double &oS);
    void iZoomb(const double &oS);
    void hZoomP();
    void hZoomM();

    void torol();
    void selFemurCirc();
    void selTibiaCirc();
    void selPatellaPoint();
    void selTibiaPoint();
    void selTibiaPlatoPoints();
    void selFureszCirc();
    void gombsel01();
    void gombsel02();
    void gombsel03();
    void gombsel04();
    void gombsel05();
    void calccTTA();
    void calcTTA();
    void exportPDF();
    void melyikelem(int i);
    void skala();
    void fureszSkala(QString s);
    void readSkala();
    void mirror();
//    void rajz();
    void help();

    void korkozepe();
    void pontosszekoto();
    QList<QLineF> ketvonal();
    void keresztezo();
    void szogmero();
    void derekas();
    void calib();
    void hossza();
    void elong();
    void furesz();
    bool calibcheck();
    void rotate();
    void rotater();
    void save();
    void szinez();

};

#endif // FRMMAIN_H
