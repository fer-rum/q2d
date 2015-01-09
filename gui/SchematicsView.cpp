#include "SchematicsView.h"

#include "SchematicsScene.h"
#include <QtDebug>

using namespace q2d::gui;

SchematicsView::SchematicsView(QWidget* parent)
    : QGraphicsView(parent) {}

//void
//SchematicsView::dragEnterEvent(QDragEnterEvent *event) {
//    qDebug() << "View: drag ENTER event";
//    event->setAccepted(true);
//    update();
//}

//void
//SchematicsView::dragMoveEvent(QDragMoveEvent *event) {
//    qDebug() << "View: drag MOVE event";
//    event->setAccepted(true);
//    update();
//}

//void
//SchematicsView::dragLeaveEvent(QDragLeaveEvent *event) {
//    qDebug() << "View: drag LEAVE event";
//    event->setAccepted(true);
//    update();
//}

//void
//SchematicsView::dropEvent(QDropEvent *event) {
//    qDebug() << "View: DROP event";
//    event->setAccepted(false);
//    update();
//}
