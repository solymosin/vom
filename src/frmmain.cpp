#include <QtGui>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QHeaderView>
#include <QDesktopServices>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QToolButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QDoubleSpinBox>
#include <QToolTip>
#include <QSettings>

#include "comtanscene.h"
#include "node.h"

#include "frmmain.h"
#include "ui_frmmain.h"
#include "xabout.h"
#include "ui_xabout.h"
#include "frmrec.h"
#include "ui_frmrec.h"
#include "frmtab.h"
#include "ui_frmtab.h"

#include "mgview.h"


frmMain::frmMain(QWidget *parent): QMainWindow(parent), ui(new Ui::frmMain){
    ui->setupUi(this);    

    QApplication::setApplicationVersion("0.992");

    /*kozepre teszi a nyito kepernyot*/
    QRect available_geom = QDesktopWidget().availableGeometry();
    QRect current_geom =  frameGeometry();

    setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
        available_geom.height() / 2 - current_geom.height() / 2,
        current_geom.width(),
        current_geom.height());
    /********************************/

    gView = new mGview(this);
    scene = new comtanScene(this);

    QHBoxLayout *layout = new QHBoxLayout;       

    //layout->addWidget(ui->dockWidget2);
    layout->addWidget(gView);
    ui->centralWidget->setLayout(layout);


    connect(ui->actionKil_p, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionN_vjegy, SIGNAL(triggered()), this, SLOT(nevjegy()));
    connect(ui->actionK_p_megnyit_sa, SIGNAL(triggered()), this, SLOT(loadRTG()));
    //connect(ui->actionT_rl_s, SIGNAL(triggered()), this, SLOT(torol()));
    connect(ui->actionMent_s_PDF_k_nt, SIGNAL(triggered()), this, SLOT(save()));
    //connect(ui->actionT_kr_z_s, SIGNAL(triggered()), this, SLOT(mirror()));
    //connect(ui->actionMent_s, SIGNAL(triggered()), this, SLOT(saveRTGtoDB()));
    //connect(ui->actionT_rolt_felv_telek, SIGNAL(triggered()), this, SLOT(listDB()));

    //connect(ui->actionZoom_In, SIGNAL(triggered()), this, SLOT(hZoomP()));
    //connect(ui->actionZoom_Out, SIGNAL(triggered()), this, SLOT(hZoomM()));

//    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), this, SLOT(skala()));

    //connect(ui->actionMozgat_s, SIGNAL(triggered()), this, SLOT(gombsel03()));
    //connect(ui->actionPontoz, SIGNAL(triggered()), this, SLOT(gombsel02()));
//    connect(ui->actionK_rz, SIGNAL(triggered()), this, SLOT(gombsel04()));
//    connect(ui->actionKalibr_ci, SIGNAL(triggered()), this, SLOT(gombsel05()));
    //connect(ui->actionMutat, SIGNAL(triggered()), this, SLOT(gombsel01()));

//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(calccTTA()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(readSkala()));
//    connect(ui->bFemurCirc, SIGNAL(clicked()), this, SLOT(selFemurCirc()));
//    connect(ui->bPatellaPoint, SIGNAL(clicked()), this, SLOT(selPatellaPoint()));
//    connect(ui->bTibiaCirc, SIGNAL(clicked()), this, SLOT(selTibiaCirc()));
//    connect(ui->bTibiaPoint, SIGNAL(clicked()), this, SLOT(selTibiaPoint()));

    //connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(korkozepe()));
//    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(pontosszekoto()));
    //connect(ui->actionVonal_k_t_pont_k_z_tt, SIGNAL(triggered()), this, SLOT(pontosszekoto()));
    //connect(ui->toolButton_8, SIGNAL(clicked()), this, SLOT(keresztezo()));
    //connect(ui->toolButton_4, SIGNAL(clicked()), this, SLOT(szogmero()));
    //connect(ui->toolButton_5, SIGNAL(clicked()), this, SLOT(derekas()));
    //connect(ui->toolButton_7, SIGNAL(clicked()), this, SLOT(calib()));
    //connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(hossza()));
    //connect(ui->toolButton_9, SIGNAL(clicked()), this, SLOT(elong()));
    //connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(furesz()));

    pid = "";
    z = 100.0;
    //tbpan->triggered();
    //ui->actionMozgat_s->trigger();
//    ui->menuMunka->setVisible(false);
    //tbpan->setChecked(true);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString("%1/db.sqlite").arg(QApplication::applicationDirPath()));

    scene->addPixmap(QPixmap(":/images/figs/Freemasonry.png"));

    gView->setScene(scene);
    gView->scale(0.5,0.5);
    gView->show();

    actcolorV = new QColor();
    actcolorF = new QColor();
    actFont = new QFont();

    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "snas", "vom");

    settings->beginGroup("qvom");
    if(settings->contains("actcolorV")){
        settings->beginGroup("actcolorV");
        actcolorV->fromRgb(settings->value("r").toInt(), settings->value("g").toInt(), settings->value("b").toInt());
        settings->endGroup();
    } else {
        actcolorV->setNamedColor("yellow");
    }
    if(settings->contains("actcolorF")){
        settings->beginGroup("actcolorF");
        actcolorV->fromRgb(settings->value("r").toInt(), settings->value("g").toInt(), settings->value("b").toInt());
        settings->endGroup();
    } else {        
        actcolorF->setNamedColor("yellow");
    }
    if(settings->contains("actFont")){
        settings->beginGroup("actFont");
        actFont->setFamily(settings->value("family").toString());
        actFont->setPixelSize(settings->value("pixelSize").toInt());
        actFont->setWeight(settings->value("weight").toInt());
        actFont->setItalic(settings->value("italic").toBool());
        settings->endGroup();
    } else {
        actFont->setFamily("Helvetica");
        actFont->setPointSize(12);
    }
    settings->endGroup();

//    db.open();
//    QSqlQuery query;
//    bool ret = false;
//    ret = query.exec("create table rtgs (id integer primary key, azon TEXT, rtg BLOB, desc TEXT, megj TEXT, dist TEXT)");
//    db.close();

//    http://qvision.sourceforge.net/index.html

    QToolButton *tbcol = new QToolButton;
    tbcol->setIcon(QIcon(":/images/figs/Color-palette-icon.png"));
    tbcol->setToolTip("Szinezés");
    connect(tbcol, SIGNAL(clicked()), this, SLOT(szinezo()));
    ui->mainToolBar->addWidget(tbcol);

    QToolButton *tbfont = new QToolButton;
    tbfont->setIcon(QIcon(":/images/figs/Fonts-icon.png"));
    tbfont->setToolTip("Betű");
    connect(tbfont, SIGNAL(clicked()), this, SLOT(betuzo()));
    ui->mainToolBar->addWidget(tbfont);

    QLabel *labline = new QLabel;
    labline->setText("Vonal: ");
    vonalv = new QDoubleSpinBox;
    vonalv->setValue(1.5);
    vonalv->setMaximum(8);
    vonalv->setMinimum(0.5);
    vonalv->setSingleStep(0.1);
    vonalv->setAlignment(Qt::AlignRight);
    vonalv->setToolTip("Vonal vastagsága pixelben");
    connect(vonalv, SIGNAL(valueChanged(double)), this, SLOT(vonalW()));
    ui->mainToolBar->addWidget(labline);
    ui->mainToolBar->addWidget(vonalv);

    ui->mainToolBar->addSeparator();

    QWidget* emptyd = new QWidget();
    emptyd->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(emptyd);

    mertek = new QDoubleSpinBox;
    mertek->setDecimals(1);
    mertek->setMinimum(0);
    mertek->setMaximum(200);
    mertek->setAlignment(Qt::AlignRight);
    QLabel *lab3 = new QLabel;
    lab3->setText("Kijelölt egyenes: ");
    ui->mainToolBar->addWidget(lab3);
    ui->mainToolBar->addWidget(mertek);
    QLabel *lab4 = new QLabel;
    lab4->setText(" mm ");
    ui->mainToolBar->addWidget(lab4);

    QToolButton *tbcal = new QToolButton;
    tbcal->setIcon(QIcon(":/images/figs/mActionMeasure.png"));
    tbcal->setToolTip("Kalibráció");
    connect(tbcal, SIGNAL(clicked()), this, SLOT(calib()));
    ui->mainToolBar->addWidget(tbcal);

    QWidget* emptya = new QWidget();
    emptya->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(emptya);

    fureszek = new QComboBox;
    fureszek->addItem("");
    fureszek->addItem("12");
    fureszek->addItem("15");
    fureszek->addItem("18");
    fureszek->addItem("21");/*20 ? 21*/
    fureszek->addItem("24");
    fureszek->addItem("27");
    fureszek->addItem("30");
    fureszek->setEditable(true);
    QLabel *lab1 = new QLabel;
    lab1->setText("Fűrész sugár: ");
    ui->mainToolBar->addWidget(lab1);
    ui->mainToolBar->addWidget(fureszek);
    QLabel *lab2 = new QLabel;
    lab2->setText(" mm ");
    ui->mainToolBar->addWidget(lab2);

    QToolButton *tbfuresz = new QToolButton;
    tbfuresz->setIcon(QIcon(":/images/figs/tf2.png"));
    tbfuresz->setToolTip("Fűrész felhelyezése");
    connect(tbfuresz, SIGNAL(clicked()), this, SLOT(furesz()));
    ui->mainToolBar->addWidget(tbfuresz);

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(empty);
    QWidget* emptye = new QWidget();
    emptye->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(emptye);

    QToolButton *tbdel = new QToolButton;
    tbdel->setIcon(QIcon(":/images/figs/Close-icon.png"));
    tbdel->setToolTip("Kijelölt elemek törlése");
    connect(tbdel, SIGNAL(clicked()), this, SLOT(torol()));
    ui->mainToolBar->addWidget(tbdel);


    /*2. toolbar*/

    //QToolBar *bar2 = new QToolBar;
    //bar2->setOrientation(Qt::Vertical);
    //bar2->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //addToolBar(Qt::LeftToolBarArea, bar2);

    QToolBar *bar2 = new QToolBar;
    bar2->setOrientation(Qt::Vertical);
    bar2->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::BottomToolBarArea | Qt::TopToolBarArea);
    addToolBar(Qt::BottomToolBarArea, bar2);


    tbpan = new QToolButton;
    tbpan->setIcon(QIcon(":/images/figs/pan.png"));
    tbpan->setToolTip("Mozgatás");
    tbpan->setCheckable(true);
    tbpan->setChecked(true);
    connect(tbpan, SIGNAL(clicked()), this, SLOT(gombsel03()));
    bar2->addWidget(tbpan);

    tbpointer = new QToolButton;
    tbpointer->setIcon(QIcon(":/images/figs/pointer.png"));
    tbpointer->setToolTip("Mutató");
    tbpointer->setCheckable(true);
    connect(tbpointer, SIGNAL(clicked()), this, SLOT(gombsel01()));
    bar2->addWidget(tbpointer);

    tbpont = new QToolButton;
    tbpont->setIcon(QIcon(":/images/figs/1265531541_edit_add.png"));
    tbpont->setToolTip("Pontozás");
    tbpont->setCheckable(true);
    connect(tbpont, SIGNAL(clicked()), this, SLOT(gombsel02()));
    bar2->addWidget(tbpont);

    tblab = new QToolButton;
    tblab->setIcon(QIcon(":/images/figs/label-icon.png"));
    tblab->setToolTip("Pontozás");
    tblab->setCheckable(true);
    connect(tblab, SIGNAL(clicked()), this, SLOT(gombsel04()));
    bar2->addWidget(tblab);


    bar2->addSeparator();

    QToolButton *tbmirror = new QToolButton;
    tbmirror->setIcon(QIcon(":/images/figs/Actions-object-flip-horizontal-icon.png"));
    tbmirror->setToolTip("Tükrözés");
    connect(tbmirror, SIGNAL(clicked()), this, SLOT(mirror()));
    bar2->addWidget(tbmirror);

//    QToolButton *tbrotate = new QToolButton;
//    tbrotate->setIcon(QIcon(":/images/figs/Editing-Rotation-Cw-icon.png"));
//    tbrotate->setToolTip("Forgatás");
//    connect(tbrotate, SIGNAL(clicked()), this, SLOT(rotate()));
//    bar2->addWidget(tbrotate);

    rot = new QSpinBox;
    rot->setValue(0);
    rot->setMaximum(180);
    rot->setMinimum(-180);
    rot->setSingleStep(1);
    rot->setSuffix("°");
    rot->setAlignment(Qt::AlignRight);
    rot->setToolTip("Objektum elfordításának szöge");
    //rot->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //connect(rot, SIGNAL(valueChanged(int)), this, SLOT(rotatO()));
    bar2->addWidget(rot);

    QToolButton *tbrotater = new QToolButton;
    tbrotater->setIcon(QIcon(":/images/figs/Editing-Rotation-Cw-icon.png"));
    tbrotater->setToolTip("Forgatás");
    connect(tbrotater, SIGNAL(clicked()), this, SLOT(rotatO()));
    bar2->addWidget(tbrotater);

    bar2->addSeparator();

    QToolButton *tbvonal = new QToolButton;
    tbvonal->setIcon(QIcon(":/images/figs/linepointer.png"));
    tbvonal->setToolTip("Vonal két pont között");
    connect(tbvonal, SIGNAL(clicked()), this, SLOT(pontosszekoto()));
    bar2->addWidget(tbvonal);

    QToolButton *tbcircentr = new QToolButton;
    tbcircentr->setIcon(QIcon(":/images/figs/App-Adobe-Acrobat-Reader-icon.png"));
    tbcircentr->setToolTip("Köréírt kör középpontja");
    kortis = false;
    subact = new QAction("Rajzoljon kört is", this);
    subact->setCheckable(true);
    subact->setChecked(kortis);
    connect(subact, SIGNAL(triggered(bool)), this, SLOT(setKortis()));
    QMenu *xmenu = new QMenu();
    xmenu->addAction(subact);
    tbcircentr->setMenu(xmenu);
    connect(tbcircentr, SIGNAL(clicked()), this, SLOT(korkozepe()));
    bar2->addWidget(tbcircentr);

    QToolButton *tbkeresztezo = new QToolButton;
    tbkeresztezo->setIcon(QIcon(":/images/figs/Symbols-Delete-icon.png"));
    tbkeresztezo->setToolTip("Metszéspont");
    connect(tbkeresztezo, SIGNAL(clicked()), this, SLOT(keresztezo()));
    bar2->addWidget(tbkeresztezo);

    bar2->addSeparator();

    deg = new QSpinBox;
    deg->setValue(90);
    deg->setMaximum(360);
    deg->setMinimum(0);
    deg->setSingleStep(1);
    deg->setSuffix("°");
    deg->setAlignment(Qt::AlignRight);
    deg->setToolTip("Hány fokot zárjon be a két egyenes? 90 fok esetén egy egyenest és egy pontot kell kijelölni. Ettől eltérő esetben csak egy egyenest.");
    bar2->addWidget(deg);

    QToolButton *tbderek = new QToolButton;
    tbderek->setIcon(QIcon(":/images/figs/Triangle-ruler-icon.png"));
    tbderek->setToolTip("Szöget bezáró egyenes");
    connect(tbderek, SIGNAL(clicked()), this, SLOT(derekas()));
    bar2->addWidget(tbderek);

    bar2->addSeparator();

    QToolButton *tbhosszabb = new QToolButton;
    tbhosszabb->setIcon(QIcon(":/images/figs/resize-diag-1-icon.png"));
    tbhosszabb->setToolTip("Egyenes meghosszabbítása");
    connect(tbhosszabb, SIGNAL(clicked()), this, SLOT(elong()));
    bar2->addWidget(tbhosszabb);

    bar2->addSeparator();

    QToolButton *tbhossza = new QToolButton;
    tbhossza->setIcon(QIcon(":/images/figs/ruler-icon.png"));
    tbhossza->setToolTip("Hosszmérő");
    connect(tbhossza, SIGNAL(clicked()), this, SLOT(hossza()));
    bar2->addWidget(tbhossza);

    QToolButton *tbszog = new QToolButton;
    tbszog->setIcon(QIcon(":/images/figs/Semicircle-ruler-icon.png"));
    tbszog->setToolTip("Szögmérő");
    connect(tbszog, SIGNAL(clicked()), this, SLOT(szogmero()));
    bar2->addWidget(tbszog);

    //bar2->addSeparator();

    //rot = new QSpinBox;
    //rot->setValue(0);
    //rot->setMaximum(180);
    //rot->setMinimum(-180);
    //rot->setSingleStep(1);
    //rot->setSuffix("°");
    //rot->setAlignment(Qt::AlignRight);
    //rot->setToolTip("Objektum elfordításának szöge");
    ////rot->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //connect(rot, SIGNAL(valueChanged(int)), this, SLOT(rotatO()));
    //bar2->addWidget(rot);


}

frmMain::~frmMain(){
    delete ui;
}


void frmMain::setKortis(){
    kortis = subact->isChecked();
    //qDebug() << kortis;
}


void frmMain::rotatO(){
    int tip = 0;
    if(scene->selectedItems().count()==0){
        gView->rotate(rot->value());
    } else {
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            tip = item->type();
            if (tip==6){
                QGraphicsLineItem *lrot = qgraphicsitem_cast<QGraphicsLineItem *>(item);

                //https://forum.qt.io/topic/17097/sample-code-for-rotating/4

                double Pi = 3.14159265358979323846264338327950288419717;
                double rotAngle = -1*rot->value() * (Pi / 180.0);
                double sinAngle = qSin(rotAngle);
                double cosAngle = qCos(rotAngle);

                int px = lrot->line().p1().x() - lrot->boundingRect().center().x();
                int py = lrot->line().p1().y() - lrot->boundingRect().center().y();

                float xnew = px * cosAngle + py * sinAngle;
                float ynew = py * cosAngle - px * sinAngle;

                qreal p1x = xnew + lrot->boundingRect().center().x();
                qreal p1y = ynew + lrot->boundingRect().center().y();

                px = lrot->line().p2().x() - lrot->boundingRect().center().x();
                py = lrot->line().p2().y() - lrot->boundingRect().center().y();

                xnew = px * cosAngle + py * sinAngle;
                ynew = py * cosAngle - px * sinAngle;

                qreal p2x = xnew + lrot->boundingRect().center().x();
                qreal p2y = ynew + lrot->boundingRect().center().y();

                scene->removeItem(scene->selectedItems().first());
                scene->addVonalB(p1x, p1y, p2x, p2y, actcolorV->toRgb(), vonalv->value());

                //lrot->prepareGeometryChange();
                //lrot->line().setLine(p1x, p1y, p2x, p2y);
                //lrot->setRotation(rot->value());

                //scene->selectedItems().first()->

                //l->line().p1().setX(p1x);
                //l->line().p1().setY(p1y);
                //l->line().p2().setX(p2x);
                //l->line().p2().setY(p2y);
                //lrot->update();
                //scene->update();

                //qDebug() << lrot->line().p1().x();

            }
            if (tip==5){
                QGraphicsPolygonItem *l = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
                l->setRotation(rot->value());
            }
        }
        //if(tip==6){
        //    QGraphicsItem *it;
      //      foreach (it, scene->items()) {
    //
            //}
            //it->setSelected(true);
            //scene->items.at(scene->items().count()-1)->setSelected(true);
            //scene->items().at(scene->items().count()-1)->setSelected(true);
            //scene->update();
        //scene->items().end()
        //}
    }
}


void frmMain::saveSettings(){

    settings->beginGroup("qvom");

    settings->beginGroup("actcolorV");
    settings->setValue("r", actcolorV->toRgb().red());
    settings->setValue("g", actcolorV->toRgb().green());
    settings->setValue("b", actcolorV->toRgb().blue());
    settings->endGroup();

    settings->beginGroup("actcolorF");
    settings->setValue("r", actcolorF->toRgb().red());
    settings->setValue("g", actcolorF->toRgb().green());
    settings->setValue("b", actcolorF->toRgb().blue());
    settings->endGroup();

    settings->beginGroup("actFont");
    settings->setValue("family", actFont->family());
    settings->setValue("pixelSize", actFont->pixelSize());
    settings->setValue("weight", actFont->weight());
    settings->setValue("italic", actFont->italic());
    settings->endGroup();

    settings->endGroup();

    settings->sync();
}

void frmMain::vonalW(){
    //int s = 0;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        //s = s+item->type();
        if (item->type()==6){
            QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(item);
            l->setPen(QPen(actcolorV->toRgb(), vonalv->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        if (item->type()==5){
            QGraphicsPolygonItem *l = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            l->setPen(QPen(actcolorV->toRgb(), vonalv->value()*3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
    }
}


void frmMain::betuzo(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont(actFont->family(), actFont->pointSize(), actFont->weight(), actFont->italic()), this, tr("Betű kiválasztása") );
    if(ok){
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            if (item->type()==8){
                QGraphicsTextItem *ti = qgraphicsitem_cast<QGraphicsTextItem *>(item);
                ti->setFont(font);
            }
            if (item->type()==6){
                if(item->childItems().count()==1){
                    QGraphicsSimpleTextItem* lab = qgraphicsitem_cast<QGraphicsSimpleTextItem *>(item->childItems().at(0));
                    lab->setFont(font);
                }
            }
        }
        actFont->setFamily(font.family());
        actFont->setPixelSize(font.pixelSize());
        //actFont->setBold(font.bold());
        actFont->setWeight(font.weight());
        actFont->setItalic(font.italic());        
        /**/
        saveSettings();
    }
}


void frmMain::szinezo(){
    QColor color = QColorDialog::getColor(actcolorV->toRgb(), this, tr("Szín választása") );
    if(color.isValid()){
        //int s = 0;
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            if (item->type()==6){
                QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(item);
                l->setPen(QPen(color, vonalv->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                if(l->childItems().count()==1){
                    QGraphicsSimpleTextItem* lab = qgraphicsitem_cast<QGraphicsSimpleTextItem *>(l->childItems().at(0));
                    lab->setBrush(color);
                }
                actcolorV = new QColor(color);
            }
            if (item->type()==5){
                QGraphicsPolygonItem *l = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
                l->setPen(QPen(color, vonalv->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                actcolorV = new QColor(color);
            }
            if (item->type()==8){
                QGraphicsTextItem *ti = qgraphicsitem_cast<QGraphicsTextItem *>(item);
                ti->setDefaultTextColor(color);
                actcolorF = new QColor(color);
            }
        }
    saveSettings();
    }
}


void frmMain::rotater(){
    //gView->rotate(-5);
    gView->rotate(rot->value());
}

void frmMain::rotate(){
    gView->rotate(5);
}


bool frmMain::calibcheck(){
    bool b = true;
    if(scene->dPix<1 or mertek->value()==0){
        b = false;
    }
    return b;
}

void frmMain::furesz(){
    if(!calibcheck()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Elmaradt a kalibráció");
        msgBox.exec();
        return;
    }

    if (scene->selectedItems().count()!=1){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 1 pontot kell kijelölni");
        msgBox.exec();
    } else {        
        if(fureszek->currentText()==""){
            return;
        }
        double m = fureszek->currentText().toDouble();
        double ptx = (m/mertek->value())*scene->dPix;
        scene->addKorB(scene->selectedItems().first()->x(), scene->selectedItems().first()->y(), ptx, vonalv->value(), actcolorV->toRgb(), ptx);
    }
}


void frmMain::elong(){
    int s = 0;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        s = s+item->type();
    }
    if (scene->selectedItems().count()!=1 or s!=6){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 1 egyenest kell kijelölni");
        msgBox.exec();
    } else {
        QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(scene->selectedItems().first());
        double dx = l->line().dx();
        double dy = l->line().dy();
        QPointF A;
        QPointF B;
        A = l->line().p1()-QPointF(dx, dy);
        B = l->line().p2()+QPointF(dx, dy);
        scene->removeItem(scene->selectedItems().first());
        scene->addVonalB(A.x(), A.y(), B.x(), B.y(), actcolorV->toRgb(), vonalv->value());
    }
}

void frmMain::calib(){
    int s = 0;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        s = s+item->type();
    }
    if (scene->selectedItems().count()!=1 or s!=6){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 1 egyenest kell kijelölni");
        msgBox.exec();
    } else {
        foreach (QGraphicsItem *item, scene->items()) {
            if(item->data(0).toString()=="calib"){
                scene->removeItem(item);
                scene->dPix = 0;
            }
        }
        QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(scene->selectedItems().first());        
        scene->dPix = l->line().length();
        scene->selectedItems().first()->setOpacity(0.9);
        l->setData(0, "calib");
        l->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
}


void frmMain::hossza(){
    if(!calibcheck()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Elmaradt a kalibráció");
        msgBox.exec();
        return;
    }

    int s = 0;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        s = s+item->type();
    }
    if (scene->selectedItems().count()!=1 or s!=6){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 1 egyenest kell kijelölni");
        msgBox.exec();
    } else {
        QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(scene->selectedItems().first());
        double h=0;
        h = (l->line().length()/scene->dPix)*mertek->value();
        ui->statusBar->showMessage(QString("Hossza: %1 mm").arg(QString::number(h,'f',1)));
        QGraphicsSimpleTextItem* lab = new QGraphicsSimpleTextItem();        

        if(l->childItems().count()>0){
            QGraphicsItem* dl;
            dl = l->childItems().at(0);
            delete dl;
        }

        lab->setText(QString("%1 mm").arg(QString::number(h,'f',1)));
        QFont font(actFont->family());
        font.setPointSize(actFont->pointSize());
        lab->setBrush(l->pen().color());
        lab->setFont(font);
        lab->setPos(l->boundingRect().center());


        double a = 360-l->line().angle();
        lab->setRotation(a);
        lab->setParentItem(l);
    }
}


void frmMain::derekas(){
    if(deg->value()==90){
        int s = 0;
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            s = s+item->type();
        }
        if (scene->selectedItems().count()!=2 or s!=11){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Figyelmezzünk!");
            msgBox.setInformativeText("Pontosan 1 egyenest és 1 pontot kell kijelölni");
            msgBox.exec();
        } else {
            QLineF l1;
            QPointF pont;
            foreach (QGraphicsItem *item, scene->selectedItems()) {
                if(item->type()==6){
                    QGraphicsLineItem *vonal = qgraphicsitem_cast<QGraphicsLineItem *>(item);
                    l1.setP1(vonal->line().p1());
                    l1.setP2(vonal->line().p2());
                } else {
                    pont.setX(item->x());
                    pont.setY(item->y());
                }
            }
            QPointF A;
            QPointF B;
            A = l1.p1();
            B = l1.p2();

    //        http://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
            double nl = sqrt((B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y()));
            double tav = ((pont.x()-A.x())*(B.y()-A.y())-(pont.y()-A.y())*(B.x()-A.x()))/nl;

            QLineF lb(l1.p1().x(), l1.p1().y(), l1.p2().x(), l1.p2().y());

            double c = sqrt(pow(l1.p1().x()-pont.x(),2)+pow(l1.p1().y()-pont.y(),2));

            double b = sqrt(pow(c,2)-pow(tav,2));
            lb.setLength(b);
            QLineF l5(pont.x(), pont.y(), lb.p2().x(), lb.p2().y());

            scene->addVonalB(l5.p1().x(), l5.p1().y(), l5.p2().x(), l5.p2().y(), actcolorV->toRgb(), vonalv->value());
        }
    } else {
        int s = 0;
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            s = s+item->type();
        }
        if (scene->selectedItems().count()!=1 or s!=6){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Figyelmezzünk!");
            msgBox.setInformativeText("Pontosan 1 egyenest kell kijelölni");
            msgBox.exec();
        } else {
            QLineF l1;
            foreach (QGraphicsItem *item, scene->selectedItems()) {
                if(item->type()==6){
                    QGraphicsLineItem *vonal = qgraphicsitem_cast<QGraphicsLineItem *>(item);
                    l1.setP1(vonal->line().p1());
                    l1.setP2(vonal->line().p2());
                }
            }
            QLineF lc(l1.p1().x(), l1.p1().y(), l1.p2().x(), l1.p2().y());
            lc.setAngle(l1.angle()+deg->value());

            scene->addVonalB(lc.p1().x(), lc.p1().y(), lc.p2().x(), lc.p2().y(), actcolorV->toRgb(), vonalv->value());
        }
    }
}

void frmMain::szogmero(){
    QList<QLineF> lns = ketvonal();
    if(lns.length()==2){
        double ba = lns.at(0).angleTo(lns.at(1));
        double bb = lns.at(1).angleTo(lns.at(0));
        if(ba>bb){
            ui->statusBar->showMessage(QString("Külső szög: %1\nBelső szög: %2").arg(ba).arg(bb));
        }
        if(ba<bb){
            ui->statusBar->showMessage(QString("Külső szög: %1\nBelső szög: %2").arg(bb).arg(ba));
        }
        if(ba==bb){
            ui->statusBar->showMessage(QString("Szög: %1").arg(ba));
        }
    }
}


void frmMain::keresztezo(){
    QList<QLineF> lns = ketvonal();
    if(lns.length()==2){
        QPointF* ip = new QPointF;
        lns.at(0).intersect(lns.at(1), ip);
        scene->addPontB(ip->x(), ip->y());
    }
}


QList<QLineF> frmMain::ketvonal(){
    QList<QLineF> lns;
    int s = 0;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        s = s+item->type();
    }
    if (scene->selectedItems().count()!=2 or s!=12){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 2 egyenest kell kijelölni");
        msgBox.exec();
    } else {
        QGraphicsLineItem *a = qgraphicsitem_cast<QGraphicsLineItem *>(scene->selectedItems().at(0));
        QGraphicsLineItem *b = qgraphicsitem_cast<QGraphicsLineItem *>(scene->selectedItems().at(1));
        QLineF l1(a->line().p1().x(), a->line().p1().y(), a->line().p2().x(), a->line().p2().y());
        QLineF l2(b->line().p1().x(), b->line().p1().y(), b->line().p2().x(), b->line().p2().y());
        lns << l1 << l2;
    }
    return lns;
}

void frmMain::pontosszekoto(){
    QList<double> xs, ys;
    if (scene->selectedItems().count()!=2){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 2 pontot kell kijelölni");
        msgBox.exec();
    } else {
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            xs.append(item->x());
            ys.append(item->y());
        }
        scene->addVonalB(xs.at(0), ys.at(0), xs.at(1), ys.at(1), actcolorV->toRgb(), vonalv->value());
    }
}

void frmMain::korkozepe(){
    QList<double> xs, ys;

    if (scene->selectedItems().count()!=3){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Figyelmezzünk!");
        msgBox.setInformativeText("Pontosan 3 pontot kell kijelölni");
        msgBox.exec();
    } else {
        foreach (QGraphicsItem *item, scene->selectedItems()) {
            xs.append(item->x());
            ys.append(item->y());
//            qDebug() << item->x() << item->y();
        }

        double a13=1.0;
        double a23=1.0;
        double a33=1.0;

        double a11=pow(xs.at(0),2)+pow(ys.at(0),2);
        double a12=ys.at(0);
        double a21=pow(xs.at(1),2)+pow(ys.at(1),2);
        double a22=ys.at(1);
        double a31=pow(xs.at(2),2)+pow(ys.at(2),2);
        double a32=ys.at(2);

        double bx = a11*a22*a33-a11*a23*a32+a13*a21*a32-a12*a21*a33+a12*a23*a31-a13*a22*a31;

    //    a11==pow(xs.at(0),2)+pow(ys.at(0),2);
        a12=xs.at(0);
    //    a21==pow(xs.at(1),2)+pow(ys.at(1),2);
        a22=xs.at(1);
    //    a31==pow(xs.at(2),2)+pow(ys.at(2),2);
        a32=xs.at(2);
        double by = -1*(a11*a22*a33-a11*a23*a32+a13*a21*a32-a12*a21*a33+a12*a23*a31-a13*a22*a31);

        a11=xs.at(0);
        a12=ys.at(0);
        a21=xs.at(1);
        a22=ys.at(1);
        a31=xs.at(2);
        a32=ys.at(2);
        double aa=a11*a22*a33-a11*a23*a32+a13*a21*a32-a12*a21*a33+a12*a23*a31-a13*a22*a31;

        double xc=bx/(2*aa);
        double yc=by/(2*aa);

        if(kortis==true){
            QLineF dist(xc, yc, xs.at(0), ys.at(0));
            scene->addKor(xc, yc, dist.length(), vonalv->value(), actcolorV->toRgb());
        }

        scene->addPontB(xc, yc);
    }
}


//void frmMain::saveRTGtoDB(){
//    if (pid==""){
//        addRTGtoDB();
//    } else {
//        editRTGtoDB();
//    }
//}

//void frmMain::updater(QString sql){
//    db.open();
//    QSqlQuery query;
//    query.exec(sql);
//    db.close();
//}


//void frmMain::editRTGtoDB(){
//    frmRec dlg(this);
//    dlg.setWindowTitle("Módosítás");

//    db.open();
//    QString sql = QString("select azon, megj from rtgs where id=%1").arg(pid);
//    QSqlQuery q01(sql);
//    QSqlRecord r01 = q01.record();
//    q01.first();
//    QString azon = q01.value(r01.indexOf("azon")).toString();
//    QString megj = q01.value(r01.indexOf("megj")).toString();


//    dlg.ui->lineEdit->setText(azon);
//    dlg.ui->textEdit->setText(megj);

//    if(dlg.exec() == QDialog::Accepted){
//        if(dlg.ui->lineEdit->text()!=""){

//            QString xml = "";
//            QList<double> FCx, FCy;
//            QList<double> TCx, TCy;
//            QList<double> PPx, PPy;
//            QList<double> TPx, TPy;

//            foreach (QGraphicsItem *item, scene->items()) {
//                if(item->data(1).toString()=="FemurCirc"){
//                    FCx.append(item->x());
//                    FCy.append(item->y());
//                    xml.append(QString("FC:%1,%2,%3;").arg(item->x()).arg(item->y()).arg(item->scale()));
//                }
//                if(item->data(1).toString()=="TibiaCirc"){
//                    TCx.append(item->x());
//                    TCy.append(item->y());
//                    xml.append(QString("TC:%1,%2,%3;").arg(item->x()).arg(item->y()).arg(item->scale()));
//                }
//                if(item->data(1).toString()=="PatellaPoint"){
//                    PPx.append(item->x());
//                    PPy.append(item->y());
//                    xml.append(QString("PP:%1,%2;").arg(item->x()).arg(item->y()));
//                }
//                if(item->data(1).toString()=="TibiaPoint"){
//                    TPx.append(item->x());
//                    TPy.append(item->y());
//                    xml.append(QString("TP:%1,%2;").arg(item->x()).arg(item->y()));
//                }
//            }
//            //xml.append(QString("KA:%1,%2;").arg(scene->dPix).arg(ui->doubleSpinBox_3->value()));

////            QString sql = QString("update rtgs set azon='%1', desc='%2', megj='%3', dist='%4' where id=%5")
////                .arg(dlg.ui->lineEdit->text()).arg(xml).arg(dlg.ui->textEdit->toPlainText()).arg(ui->lineEdit->text()).arg(pid);
////            QSqlQuery query;
////            query.exec(sql);

//        }
//    }

//    db.close();
//}


//void frmMain::listDB(){
//    frmTab dlg(this);
//    dlg.setWindowTitle("Tárolt felvételek");

//    db.open();

//    QString sql = "select azon, dist, id from rtgs";

//    QSqlQueryModel *model2 = new QSqlQueryModel();
//    model2->setQuery(sql);
//    model2->setHeaderData(0, Qt::Horizontal, "Azonos­tó");
//    model2->setHeaderData(1, Qt::Horizontal, "Távolság");
//    model2->setHeaderData(2, Qt::Horizontal, "id");
//    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
//    sort_filter->setSortLocaleAware(true);
//    sort_filter->setSourceModel(model2);

//    dlg.ui->tableView->setModel(sort_filter);
//    dlg.ui->tableView->resizeColumnsToContents();
//    dlg.ui->tableView->setSortingEnabled(true);
//    dlg.ui->tableView->sortByColumn(0);

//    sort_filter->sort(0, Qt::AscendingOrder);
//    db.close();

//    if(dlg.exec() == QDialog::Accepted){
//        db.open();
//        QModelIndex idx;
//        idx = dlg.ui->tableView->selectionModel()->currentIndex();
//        pid = dlg.ui->tableView->model()->data(idx.sibling(idx.row(),2)).toString();

//        sql = QString("select rtg, desc from rtgs where id=%1").arg(pid);
//        QSqlQuery q01(sql);
//        QSqlRecord r01 = q01.record();
//        q01.first();

//        scene->clear();
//        gView->close();

//        QPixmap pixmap = QPixmap();
//        pixmap.loadFromData(q01.value(r01.indexOf("rtg")).toByteArray());
//        scene->addPixmap(pixmap);
//        gView->setRenderHint(QPainter::Antialiasing);
//        gView->setCacheMode(QGraphicsView::CacheBackground);
//        gView->setDragMode(QGraphicsView::ScrollHandDrag);
//        gView->setScene(scene);
//        gView->show();

//        QString xml = q01.value(r01.indexOf("desc")).toString();

////        qDebug() << xml;

//        xml = xml.left(xml.length()-1);
//        QStringList lst = xml.split(";");
//        for(int i=0; i<lst.length(); i++){
//            QString k = lst.at(i).left(2);
//            if(k=="TP"){
//                QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
//                scene->addPont(ls.at(0).toDouble(), ls.at(1).toDouble(), "TibiaPoint");
//            } else if (k=="PP"){
//                QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
//                scene->addPont(ls.at(0).toDouble(), ls.at(1).toDouble(), "PatellaPoint");
//            } else if (k=="TC"){
//                QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
//                //scene->addKor(ls.at(0).toDouble(), ls.at(1).toDouble(), ls.at(2).toDouble(),"TibiaCirc");
//            } else if (k=="FC"){
//                QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
//                //scene->addKor(ls.at(0).toDouble(), ls.at(1).toDouble(), ls.at(2).toDouble(),"FemurCirc");
//            } else if (k=="KA"){
//                QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
//                scene->dPix =  ls.at(0).toDouble();
//                //ui->doubleSpinBox_3->setValue(ls.at(1).toDouble());
//            }
//        }

////        ui->bFemurCirc->setChecked(true);
////        ui->bPatellaPoint->setChecked(true);
////        ui->bTibiaCirc->setChecked(true);
////        ui->bTibiaPoint->setChecked(true);
////        ui->lineEdit->setText("");
//        z = 100.0;

//        db.close();

//    }

//////"TP:409,681;PP:658,304;TC:675.5,689.833,2.8;FC:839.667,572.333,2.4;FC:856.667,547.167,2.2;"
//////    scene->addKor(839.667, 572.333, 2.4, "FemurCirc");
//////TibiaCirc, PatellaPoint, TibiaPoint

////    QString xml = "TP:409,681;PP:658,304;TC:675.5,689.833,2.8;FC:839.667,572.333,2.4;FC:856.667,547.167,2.2;";
////    xml = xml.left(xml.length()-1);
////    QStringList lst = xml.split(";");
////    for(int i=0; i<lst.length(); i++){
////        QString k = lst.at(i).left(2);
////        if(k=="TP"){
////            QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
////            scene->addPont(ls.at(0).toDouble(), ls.at(1).toDouble(), "TibiaPoint");
////        } else if (k=="PP"){
////            QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
////            scene->addPont(ls.at(0).toDouble(), ls.at(1).toDouble(), "PatellaPoint");
////        } else if (k=="TC"){
////            QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
////            scene->addKor(ls.at(0).toDouble(), ls.at(1).toDouble(), ls.at(2).toDouble(),"TibiaCirc");
////        } else if (k=="FC"){
////            QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
////            scene->addKor(ls.at(0).toDouble(), ls.at(1).toDouble(), ls.at(2).toDouble(),"FemurCirc");
////        } else if (k=="KA"){
////            QStringList ls = lst.at(i).right(lst.at(i).length()-3).split(",");
////            scene->dPix =  ls.at(0).toDouble();
////            ui->doubleSpinBox_3->setValue(ls.at(1).toDouble());
////        }
////    }

//}


//void frmMain::addRTGtoDB(){
////    QString xml = "";
////    qDebug() << xml;
//////"TP:409,681;PP:658,304;TC:675.5,689.833,2.8;FC:839.667,572.333,2.4;FC:856.667,547.167,2.2;"

//    frmRec dlg(this);
//    dlg.setWindowTitle("Mentés adatbázisba");

//    if(dlg.exec() == QDialog::Accepted){
//        if(dlg.ui->lineEdit->text()!=""){
//            QString sql = "insert into rtgs (azon, rtg, desc, megj, dist) values(?, ?, ?, ?, ?)";

//            QFile fileA(rtgFile);
//            if (!fileA.open(QIODevice::ReadOnly)) return;
//            QByteArray byteArray = fileA.readAll();

//            QString xml = "";
//            QList<double> FCx, FCy;
//            QList<double> TCx, TCy;
//            QList<double> PPx, PPy;
//            QList<double> TPx, TPy;

//            foreach (QGraphicsItem *item, scene->items()) {
//                if(item->data(1).toString()=="FemurCirc"){
//                    FCx.append(item->x());
//                    FCy.append(item->y());
//                    xml.append(QString("FC:%1,%2,%3;").arg(item->x()).arg(item->y()).arg(item->scale()));
//                }
//                if(item->data(1).toString()=="TibiaCirc"){
//                    TCx.append(item->x());
//                    TCy.append(item->y());
//                    xml.append(QString("TC:%1,%2,%3;").arg(item->x()).arg(item->y()).arg(item->scale()));
//                }
//                if(item->data(1).toString()=="PatellaPoint"){
//                    PPx.append(item->x());
//                    PPy.append(item->y());
//                    xml.append(QString("PP:%1,%2;").arg(item->x()).arg(item->y()));
//                }
//                if(item->data(1).toString()=="TibiaPoint"){
//                    TPx.append(item->x());
//                    TPy.append(item->y());
//                    xml.append(QString("TP:%1,%2;").arg(item->x()).arg(item->y()));
//                }
//            }
//            //xml.append(QString("KA:%1,%2;").arg(scene->dPix).arg(ui->doubleSpinBox_3->value()));

//            db.open();

//            QSqlQuery query;
//            query.prepare(sql);
//            query.addBindValue(dlg.ui->lineEdit->text());
//            query.addBindValue(byteArray);
//            query.addBindValue(xml);
//            query.addBindValue(dlg.ui->textEdit->toPlainText());
////            query.addBindValue(ui->lineEdit->text());
//            query.exec();

//            db.close();
//        }
//    }
//}

void frmMain::loadRTG(){
    scene->clear();
    gView->resetMatrix();

    rtgFile = QFileDialog::getOpenFileName(this, "RTG-felvétel megnyitása", "", "Képfájlok (*.png *.jpg *.tif)");

    gView->setRenderHint(QPainter::Antialiasing);
    gView->setCacheMode(QGraphicsView::CacheBackground);
    gView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene->addPixmap(QPixmap(rtgFile));
    gView->setScene(scene);
    gView->scale(1,1);
    gView->show();

    pid = "";
    z = 100.0;
}


void frmMain::mirror(){
    scene->clear();
    QImage im(rtgFile);
    QImage im2 = im.mirrored(true, false);
    QPixmap pix = QPixmap::fromImage(im2);
    scene->addPixmap(pix);
}

void frmMain::melyikelem(int i){
    scene->gombKijelol(i);
}

//void frmMain::fureszSkala(QString s){
//    double m = s.toDouble();
//    double w = 0;
//    if (m!=0){
//        foreach (QGraphicsItem *item, scene->items()) {
//            if(item->data(1).toString()=="FureszCirc"){
//                w = item->shape().boundingRect().width()-1; /*ha kivonom ezt az 1 pontot, akkor lesz pontos a kör átmérője*/
//            }
//        }

//        //double ptx = (m/ui->doubleSpinBox_3->value())*scene->dPix;
//        double ptx = (m/mertek->value())*scene->dPix;
////        QGraphicsItem *nit = 0;
//        foreach (QGraphicsItem *item, scene->items()) {
//            if(item->data(1).toString()=="FureszCirc"){
////                nit = item;
//                item->setScale((ptx/w)*2);
////                item->update(nit->boundingRect());
//            }
//        }
//    }

////    qDebug() << w;
//}

//void frmMain::help(){
//    foreach (QGraphicsItem *item, scene->items()) {
//        if(item->data(1).toString()=="FureszCirc"){
//            qDebug() << item->boundingRect().width();
//            qDebug() << item->scale();
//        }
//    }
//}

//void frmMain::calcTTA(){
//    QList<double> FCx, FCy;
//    QList<double> PPx, PPy;
//    QList<double> TPx, TPy;
//    QList<double> TPPx, TPPy;
//    double cx = 0;
//    double cy = 0;
//    double cr = 0;
//    double cs = 1;
//    int ok = 0;

//    foreach (QGraphicsItem *item, scene->items()) {
//        if(item->data(1).toString()=="FureszCirc"){
//            FCx.append(item->x());
//            FCy.append(item->y());
//            cx = FCx.at(0);
//            cy = FCy.at(0);
//            cs = item->scale();
//            cr = cs*(item->shape().boundingRect().width()/2);
//            ok++;
//        }
//        if(item->data(1).toString()=="TibiaPlatoPoint"){
//            TPPx.append(item->x());
//            TPPy.append(item->y());
//            ok++;
//        }
//        if(item->data(1).toString()=="PatellaPoint"){
//            PPx.append(item->x());
//            PPy.append(item->y());
//            ok++;
//        }
//        if(item->data(1).toString()=="TibiaPoint"){
//            TPx.append(item->x());
//            TPy.append(item->y());
//            ok++;
//        }
//    }

////    qDebug() << cr;

////    ui->lineEdit->setText("");

//    if(ok==5){
//        QLineF l1(TPPx.at(0), TPPy.at(0), TPPx.at(1), TPPy.at(1));
//        QPen pen1(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//        scene->addLine(l1, pen1);

//        QLineF l2(TPPx.at(0), TPPy.at(0), TPPx.at(1), TPPy.at(1));
//        l2.setAngle(90+l2.angle());
////        scene->addLine(l2, pen1);

//        QLineF l3(PPx.at(0), PPy.at(0), l2.p1().x()+(PPx.at(0)-l2.p2().x()), l2.p1().y()+(PPy.at(0)-l2.p2().y()));
//        l3.setLength(l3.length()*5);
////        scene->addLine(l3, pen1);

////        http://www.melloland.com/scripts-and-tutos/collision-detection-between-circles-and-lines

//        double ax = l3.p1().x();
//        double ay = l3.p1().y();
//        double bx = l3.p2().x();
//        double by = l3.p2().y();

//        double vx = bx - ax;
//        double vy = by - ay;
//        double xdiff = ax - cx;
//        double ydiff = ay - cy;
//        double a = qPow(vx, 2) + qPow(vy, 2);
//        double b = 2 * ((vx * xdiff) + (vy * ydiff));
//        double c = qPow(xdiff, 2) + qPow(ydiff, 2) - qPow(cr, 2);
//        double quad = qPow(b, 2) - (4 * a * c);

//        QList<double> ixs, iys;

//        if (quad >= 0){
//            // An infinite collision is happening, but let's not stop here
//            float quadsqrt=sqrt(quad);
//            for (int i = -1; i <= 1; i += 2) {
//                // Returns the two coordinates of the intersection points
//                float t = (i * -b + quadsqrt) / (2 * a);
//                float x = ax + (i * vx * t);
//                float y = ay + (i * vy * t);
//                ixs.append(x);
//                iys.append(y);
//                // If one of them is in the boundaries of the segment, it collides
////                if (x >= min(ax, bx) && x <= max(ax, bx) && y >= min(ay, by) && y <= max(ay, by)) return true;
//            }
//        }

//        double ix = 0;
//        double iy = 0;
//        if(ixs.length()>1){
//            if(iys.at(0)<iys.at(1)){
//                ix = ixs.at(0);
//                iy = iys.at(0);
//            } else {
//                ix = ixs.at(1);
//                iy = iys.at(1);
//            }
//        } else if (ixs.length()==1){
//            ix = ixs.at(0);
//            iy = iys.at(0);
//        } else if (ixs.length()==0){
//            return;
//        }

//        QLineF l4(PPx.at(0), PPy.at(0), ix, iy);
//        QPen pen2(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        scene->addLine(l4, pen2);

//        QLineF l5(ix, iy, TPx.at(0), TPy.at(0));
//        scene->addLine(l5, pen2);

////        ui->lineEdit_2->setText(QString::number((l5.length()/scene->dPix)*ui->doubleSpinBox_3->value(),'f',1));

//        QLineF l6(cx, cy, TPx.at(0), TPy.at(0));
//        QLineF l7(cx, cy, ix, iy);
//        scene->addLine(l6, pen2);
//        scene->addLine(l7, pen2);

////        ui->lineEdit_4->setText(QString::number(l6.angleTo(l7), 'f', 1));



////        qDebug() << fabs(l1.p1().x() - PPx.at(0));
////        qDebug() << fabs(l1.p2().x() - PPx.at(0));

//    }

//}



//void frmMain::calccTTA(){
//    QList<double> FCx, FCy;
//    QList<double> TCx, TCy;
//    QList<double> PPx, PPy;
//    QList<double> TPx, TPy;
//    int ok=0;

//    foreach (QGraphicsItem *item, scene->items()) {
//        if(item->data(1).toString()=="FemurCirc"){
//            FCx.append(item->x());
//            FCy.append(item->y());
//            ok++;
//        }
//        if(item->data(1).toString()=="TibiaCirc"){
//            TCx.append(item->x());
//            TCy.append(item->y());
//            ok++;
//        }
//        if(item->data(1).toString()=="PatellaPoint"){
//            PPx.append(item->x());
//            PPy.append(item->y());
//            ok++;
//        }
//        if(item->data(1).toString()=="TibiaPoint"){
//            TPx.append(item->x());
//            TPy.append(item->y());
//            ok++;
//        }
//    }

////    ui->lineEdit->setText("");

//    if(ok==4){
//        QLineF l1(FCx.at(0), FCy.at(0), TCx.at(0), TCy.at(0));
//        QPen pen1(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//        QLineF l2(PPx.at(0), PPy.at(0), TCx.at(0)+(PPx.at(0)-FCx.at(0)), TCy.at(0)+PPy.at(0)-FCy.at(0));
//        QPen pen2(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//        QLineF l3(0.0, TPy.at(0), TPx.at(0), TPy.at(0));

//        QPointF* ip= new QPointF;
//        l2.intersect(l3, ip);
//        QLineF l4(ip->x(), ip->y(), TPx.at(0), TPy.at(0));
////        scene->addLine(l4, pen2);

//        QPointF A;
//        QPointF B;
//        A = l2.p1();
//        B = l2.p2();

////        http://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
////        public double pointToLineDistance(Point A, Point B, Point P)
////        {
////         double normalLength = Math.sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
////         return Math.abs((P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x)) / normalLength;
////        }
//        double nl = sqrt((B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y()));
//        double tav = ((TPx.at(0)-A.x())*(B.y()-A.y())-(TPy.at(0)-A.y())*(B.x()-A.x()))/nl;
//        tav = fabs(tav);

//        if(mertek->value()!=0.0){
////            tav = (tav/scene->dPix)*ui->doubleSpinBox_3->value();
////            ui->lineEdit->setText(QString("%1 mm").arg((tav/scene->dPix)*ui->doubleSpinBox_3->value()));
//        } else {
////            ui->lineEdit->setText(QString("%1").arg(tav));
//        }

////        qDebug() << fabs(tav);
////        qDebug() << l4.length();

//        QLineF l5(TPx.at(0), TPy.at(0), 0.0, TPy.at(0));
//        l5.setLength(tav);
//        l5.setAngle(90+(180-l2.angleTo(l4)));

//        scene->addLine(l1, pen1);

//        QPointF* ip2= new QPointF;
//        l2.intersect(l5, ip2);
//        QLineF l6(PPx.at(0), PPy.at(0), ip2->x(), ip2->y());
//        l2.setP1(QPointF(TPx.at(0), TPy.at(0)));
//        l2.setP2(QPointF(ip2->x(), ip2->y()));
//        l6.setLength(l6.length()*1.1);

////        QLineF l4(ip->x(), ip->y(), TPx.at(0), TPy.at(0));

////        l2.setLength(l2.length()*10);

//        scene->addLine(l6, pen2);
//        scene->addLine(l5, pen2);

////        qDebug() << l5.angleTo(l2);

////        qDebug() << l1.length() << l2.length() << l3.length() << l4.length() << l5.length() << l6.length();

//    }


//    if(ok==5){
//        if(FCx.count()==2){
//            QLineF l0(FCx.at(0), FCy.at(0), FCx.at(1), FCy.at(1));

//            QLineF l1(l0.pointAt(0.5).x(), l0.pointAt(0.5).y(), TCx.at(0), TCy.at(0));
//            QPen pen1(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//            QLineF l2(PPx.at(0), PPy.at(0), TCx.at(0)+(PPx.at(0)-l0.pointAt(0.5).x()), TCy.at(0)+PPy.at(0)-l0.pointAt(0.5).y());
//            QPen pen2(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//            QLineF l3(0.0, TPy.at(0), TPx.at(0), TPy.at(0));

//            QPointF* ip= new QPointF;
//            l2.intersect(l3, ip);
//            QLineF l4(ip->x(), ip->y(), TPx.at(0), TPy.at(0));

//            QPointF A;
//            QPointF B;
//            A = l2.p1();
//            B = l2.p2();

//            double nl = sqrt((B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y()));
//            double tav = ((TPx.at(0)-A.x())*(B.y()-A.y())-(TPy.at(0)-A.y())*(B.x()-A.x()))/nl;
//            tav = fabs(tav);

//            if(mertek->value()!=0.0){
////                ui->lineEdit->setText(QString("%1 mm").arg((tav/scene->dPix)*ui->doubleSpinBox_3->value()));
//            } else {
////                ui->lineEdit->setText(QString("%1").arg(tav));
//            }

//            QLineF l5(TPx.at(0), TPy.at(0), 0.0, TPy.at(0));
//            l5.setLength(tav);
//            l5.setAngle(90+(180-l2.angleTo(l4)));

//            scene->addLine(l0, pen1);
//            scene->addLine(l1, pen1);

//            QPointF* ip2= new QPointF;
//            l2.intersect(l5, ip2);
//            QLineF l6(PPx.at(0), PPy.at(0), ip2->x(), ip2->y());
//            l2.setP1(QPointF(TPx.at(0), TPy.at(0)));
//            l2.setP2(QPointF(ip2->x(), ip2->y()));
//            l6.setLength(l6.length()*1.1);

//            scene->addLine(l6, pen2);
//            scene->addLine(l5, pen2);

//        }
//    }

//}

void frmMain::gombsel01(){
    if(tbpointer->isChecked()==true){
        scene->gombKijelol(0);
        tbpan->setChecked(false);
        tbpont->setChecked(false);
        tblab->setChecked(false);
//        ui->actionK_rz->setChecked(false);
//        ui->actionKalibr_ci->setChecked(false);
        gView->setCursor(Qt::ArrowCursor);
        gView->setDragMode(QGraphicsView::NoDrag);
    }
}

void frmMain::gombsel05(){
//    if(ui->actionKalibr_ci->isChecked()==true){
//        scene->gombKijelol(3);
//        ui->actionMozgat_s->setChecked(false);
//        ui->actionMutat->setChecked(false);
//        ui->actionPontoz->setChecked(false);
//        ui->actionK_rz->setChecked(false);
//        gView->setCursor(Qt::ArrowCursor);
//        gView->setDragMode(QGraphicsView::NoDrag);
//    }
}

void frmMain::gombsel02(){
    if(tbpont->isChecked()==true){
        scene->gombKijelol(1);
        tbpan->setChecked(false);
        tbpointer->setChecked(false);
        tblab->setChecked(false);
//        ui->actionK_rz->setChecked(false);
//        ui->actionKalibr_ci->setChecked(false);
        gView->setCursor(Qt::CrossCursor);
        gView->setDragMode(QGraphicsView::NoDrag);
    }
}

void frmMain::gombsel04(){
    if(tblab->isChecked()==true){
        scene->gombKijelol(4);
        tbpan->setChecked(false);
        tbpointer->setChecked(false);
        tbpont->setChecked(false);
        gView->setCursor(Qt::CrossCursor);
        gView->setDragMode(QGraphicsView::NoDrag);
    }
//    if(ui->actionK_rz->isChecked()==true){
//        scene->gombKijelol(2);
//        ui->actionMozgat_s->setChecked(false);
//        ui->actionMutat->setChecked(false);
//        ui->actionPontoz->setChecked(false);
//        ui->actionKalibr_ci->setChecked(false);
//        gView->setCursor(Qt::CrossCursor);
//        gView->setDragMode(QGraphicsView::NoDrag);
//    }
}

void frmMain::gombsel03(){
    if(tbpan->isChecked()==true){
        scene->gombKijelol(0);
        tbpont->setChecked(false);
//        ui->actionK_rz->setChecked(false);
//        ui->actionKalibr_ci->setChecked(false);
        tbpointer->setChecked(false);
        tblab->setChecked(false);
        gView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void frmMain::skala(){
    if (scene->selectedItems().count()>0){
        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
        if(item->data(0).toString()=="circle"){
//            item->setScale(ui->doubleSpinBox_2->value());
        }
    }
}

void frmMain::readSkala(){
    if (scene->selectedItems().count()>0){
        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
        if(item->data(0).toString()=="circle"){
//            ui->doubleSpinBox_2->setValue(item->scale());
        }
    }
}


//void frmMain::selFemurCirc(){
//    if (scene->selectedItems().count()>2){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Vagy 1 vagy 2 kört kell kijelölni");
//        msgBox.exec();
//    } else if (scene->selectedItems().count()==0){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Vagy 1 vagy 2 kört kell kijelölni");
//        msgBox.exec();
//    } else if (scene->selectedItems().count()==1) {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().at(0));
//        if(item->data(0).toString()!="circle"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Kört kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "FemurCirc");
//        }
//    } else if (scene->selectedItems().count()==2) {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().at(0));
//        if(item->data(0).toString()!="circle"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Kört kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "FemurCirc");
//        }
//        item = qgraphicsitem_cast<node *>(scene->selectedItems().at(1));
//        if(item->data(0).toString()!="circle"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Kört kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "FemurCirc");
//        }
//    }
//}

//void frmMain::selTibiaCirc(){
//    if (scene->selectedItems().count()!=1){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Pontosan 1 kört kell kijelölni");
//        msgBox.exec();
//    } else {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
//        if(item->data(0).toString()!="circle"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Kört kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "TibiaCirc");
//            QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//            item->setPen(pen);
//        }
//    }
//}

//void frmMain::selFureszCirc(){
//    if (scene->selectedItems().count()!=1){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Pontosan 1 kört kell kijelölni");
//        msgBox.exec();
//    } else {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
//        if(item->data(0).toString()!="circle"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Kört kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "FureszCirc");
//            QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//            item->setPen(pen);
//        }
//    }
//}


//void frmMain::selTibiaPlatoPoints(){
//    if (scene->selectedItems().count()!=2){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Pontosan 2 pontot kell kijelölni");
//        msgBox.exec();
//    } else {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
//        if(item->data(0).toString()!="pont"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Pontot kell kijelölni");
//            msgBox.exec();
//        } else {
//            foreach (QGraphicsItem *item, scene->selectedItems()) {
//                item->setData(1, "TibiaPlatoPoint");
//            }
//        }
//    }
//}


//void frmMain::selPatellaPoint(){
//    if (scene->selectedItems().count()!=1){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Pontosan 1 pontot kell kijelölni");
//        msgBox.exec();
//    } else {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
//        if(item->data(0).toString()!="pont"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Pontot kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "PatellaPoint");
//        }
//    }
//}

//void frmMain::selTibiaPoint(){
//    if (scene->selectedItems().count()!=1){
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText("Figyelmezzünk!");
//        msgBox.setInformativeText("Pontosan 1 pontot kell kijelölni");
//        msgBox.exec();
//    } else {
//        node *item = qgraphicsitem_cast<node *>(scene->selectedItems().first());
//        if(item->data(0).toString()!="pont"){
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText("Figyelmezzünk!");
//            msgBox.setInformativeText("Pontot kell kijelölni");
//            msgBox.exec();
//        } else {
//            item->setData(1, "TibiaPoint");
//        }
//    }
//}

void frmMain::torol(){
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        scene->removeItem(item);
    }
}

void frmMain::hZoomP(){
    z = z + 10.0;
    iZoom(z);
}

void frmMain::hZoomM(){
    z = z - 10.0;
    iZoom(z);
}


void frmMain::iZoom(const double &oS){
    double uS = oS / 100.0;
    QMatrix oM = gView->matrix();
    gView->resetMatrix();
    gView->translate(oM.dx(), oM.dy());
    gView->scale(uS,uS);
    gView->repaint();
}

void frmMain::iZoomb(const double &oS){
    double uS = oS / 100.0;
    QMatrix oM = gView->matrix();
    gView->translate(oM.dx(), oM.dy());
    gView->scale(uS,uS);
    gView->repaint();
}

void frmMain::save(){
    QString filters("*.jpg;;*.png;;*.pdf");
    QString dFilter("*.jpg");

    QFileDialog dlg(0, "Mentés fájlként", QDir::currentPath(), filters);
    dlg.selectNameFilter(dFilter);
    dlg.setAcceptMode(QFileDialog::AcceptSave);

    if(dlg.exec() == QDialog::Accepted){
        QString fileName = dlg.selectedFiles()[0];
        QString ft = dlg.selectedNameFilter();
        if (!fileName.isEmpty()){
            if (!fileName.isEmpty()){
                fileName.append(ft.right(4));
            }
        }

        if(ft=="*.pdf"){
            #ifndef QT_NO_PRINTER
                QPrinter *printer;
                printer = new QPrinter(QPrinter::HighResolution);
                printer->setOutputFormat(QPrinter::PdfFormat);
                printer->setOutputFileName(fileName);
                QPainter pp(printer);
                scene->render(&pp);
            #endif
        }
        if (ft=="*.jpg"){
            scene->clearSelection();
            scene->setSceneRect(scene->itemsBoundingRect());
            QImage image(gView->sceneRect().size().toSize(), QImage::Format_ARGB32);
            image.fill(Qt::transparent);
            QPainter painter(&image);
            gView->scene()->render(&painter);
            int dpm = 300 / 0.0254; // ~300 DPI
            image.setDotsPerMeterX(dpm);
            image.setDotsPerMeterY(dpm);
            image.save(fileName, "JPEG", 100);
        }
        if (ft=="*.png"){
            scene->clearSelection();
            scene->setSceneRect(scene->itemsBoundingRect());
            QImage image(gView->sceneRect().size().toSize(), QImage::Format_ARGB32);
            image.fill(Qt::transparent);
            QPainter painter(&image);
            gView->scene()->render(&painter);
            int dpm = 300 / 0.0254; // ~300 DPI
            image.setDotsPerMeterX(dpm);
            image.setDotsPerMeterY(dpm);
            image.save(fileName, "PNG", 100);
        }
    }
}

void frmMain::exportPDF(){
//#ifndef QT_NO_PRINTER
////! [0]
//    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");
//    if (!fileName.isEmpty()){
//        if (QFileInfo(fileName).suffix().isEmpty())
//            fileName.append(".pdf");
//        QPrinter *printer;
//        printer = new QPrinter(QPrinter::HighResolution);
//        printer->setOutputFormat(QPrinter::PdfFormat);
//        printer->setOutputFileName(fileName);
//        QPainter pp(printer);
//        scene->render(&pp);

////        QPainter painter;
////        painter.begin(&printer);
////        painter.drawImage(printer.pageRect(), QImage("../proba.jpg");
////        painter.end();
//    }
////! [0]
//#endif
//    QPrinter *printer;
//    QPainter painter;
//    painter.begin(&printer);
//    painter.drawImage(printer.pageRect(), QImage("../proba.jpg"));
//    painter.end();


    //QPixmap pixMap = QPixmap::grabWidget(gView);
    //QPixmap pixMap = gView->grab(); //QPixmap::grabWidget(gView);
    //pixMap.save("proba2.jpg","JPEG");

    //QGraphicsView *gv = new QGraphicsView;
    //gv = gView;
    //gv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //gv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap pixMap = gView->grab();
    pixMap.save("proba2.jpg","JPEG",100);

    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
    QImage image(gView->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    gView->scene()->render(&painter);
    int dpm = 300 / 0.0254; // ~300 DPI
    image.setDotsPerMeterX(dpm);
    image.setDotsPerMeterY(dpm);
    image.save("file_name.png");

//    QImage image = selectedScene->toImage(size);
//    image.save(fileName);



}

void frmMain::changeEvent(QEvent *e){
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void frmMain::nevjegy(){
    xAbout dlg(this);
    dlg.ui->plainTextEdit->appendPlainText(QString("\nVerzió: %1").arg(QApplication::applicationVersion()));

    if(dlg.exec() == QDialog::Accepted)    {

    }
}
