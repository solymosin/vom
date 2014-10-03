#include <QDebug>
#include <QWheelEvent>

#include "mgview.h"

mGview::mGview(QWidget *parent): QGraphicsView(parent){

}


void mGview::wheelEvent(QWheelEvent *event){
//    int z = event->delta();
//    qDebug() << z;

//    qDebug() << event->delta();
//    if (e->modifiers().testFlag(Qt::ControlModifier)){ // zoom only when CTRL key pressed
//        int numSteps = e->delta() / 15 / 8;

//        if (numSteps == 0) {
//            e->ignore();
//            return;
//        }
//        qreal sc = pow(1.25, numSteps); // I use scale factor 1.25
//        this->zoom(sc, mapToScene(e->pos()));
//        e->accept();
//    }
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}


void mGview::zoom(qreal factor, QPointF centerPoint){
    scale(factor, factor);
    centerOn(centerPoint);
}

