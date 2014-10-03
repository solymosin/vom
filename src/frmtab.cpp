#include "frmtab.h"
#include "ui_frmtab.h"

frmTab::frmTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmTab)
{
    ui->setupUi(this);
}

frmTab::~frmTab()
{
    delete ui;
}
