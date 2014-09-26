#ifndef FRMREC_H
#define FRMREC_H

#include <QDialog>

namespace Ui {
class frmRec;
}

class frmRec : public QDialog
{
    Q_OBJECT
    
public:
    explicit frmRec(QWidget *parent = 0);
    ~frmRec();
    Ui::frmRec *ui;

};

#endif // FRMREC_H
