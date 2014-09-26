#ifndef MGVIEW_H
#define MGVIEW_H

#include <QGraphicsView>

class mGview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit mGview(QWidget *parent = 0);
    void zoom(qreal factor, QPointF centerPoint);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    bool isTouched;
    QPointF mousePos;
};

#endif // MGVIEW_H

