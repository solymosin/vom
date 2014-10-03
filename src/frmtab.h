#ifndef FRMTAB_H
#define FRMTAB_H

#include <QDialog>

namespace Ui {
class frmTab;
}

class frmTab : public QDialog
{
    Q_OBJECT
    
public:
    explicit frmTab(QWidget *parent = 0);
    ~frmTab();
    Ui::frmTab *ui;


};

#endif // FRMTAB_H
