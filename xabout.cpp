#include "xabout.h"
#include "ui_xabout.h"

xAbout::xAbout(QWidget *parent): QDialog(parent), ui(new Ui::xAbout){
    ui->setupUi(this);
}

xAbout::~xAbout(){
    delete ui;
}
