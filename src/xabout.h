#ifndef XABOUT_H
#define XABOUT_H

#include <QDialog>

namespace Ui {
class xAbout;
}

class xAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit xAbout(QWidget *parent = 0);
    ~xAbout();
    Ui::xAbout *ui;

};

#endif // XABOUT_H
