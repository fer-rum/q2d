
#include "../model/Component.h"
#include "Schematic.h"
#include "SchematicsView.h"

#include <QtDebug>

using namespace q2d::gui;

SchematicsView::SchematicsView(QWidget* parent)
    : QGraphicsView(parent) {}

void
SchematicsView::setScene(Schematic* scene) {
    Q_CHECK_PTR(scene);

    QGraphicsView::setScene(scene);

}

void
SchematicsView::updateScene(const QList<QRectF> &rects) {
    QGraphicsView::updateScene(rects);
}
