#include "frmrec.h"
#include "ui_frmrec.h"

frmRec::frmRec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRec)
{
    ui->setupUi(this);
}

frmRec::~frmRec()
{
    delete ui;
}
