
#include "../model/Component.h"
#include "Schematic.h"
#include "SchematicsView.h"

#include <QtDebug>

using namespace q2d::gui;

SchematicsView::SchematicsView(QWidget* parent)
    : QGraphicsView(parent) {}

void
SchematicsView::resizeEvent( QResizeEvent* e ) {
    double w = ( e->size().width());
    double h = ( e->size().height());
    QGraphicsView::resizeEvent(e);
    this->scene()->setSceneRect(0, 0, w, h);
}

void
SchematicsView::setScene(Schematic *scene){

    QGraphicsView::setScene(scene);
    connect(scene, &Schematic::signal_componentDetailRequested,
            this, &SchematicsView::signal_componentDetailRequested);

}
