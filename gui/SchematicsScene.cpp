#include "SchematicsScene.h"

#include "../Constants.h"
#include "../Document.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QLineF>
#include <QPainter>
#include <QtDebug>
#include <QtSvg/QGraphicsSvgItem>

using namespace q2d::gui;
using namespace q2d::constants;

SchematicsScene::SchematicsScene(Document* parent)
    : QGraphicsScene(parent) {

// for debug purposes
//    this->addLine(0, -100, 0, 100);
//    this->addLine(-100, 0, 100, 0);
}

q2d::Document*
SchematicsScene::document() const {
    return qobject_cast<Document*>(parent());
}

void
SchematicsScene::drawBackground(QPainter* painter, const QRectF &rect) {

    // TODO read behaviour from settings
    QPen pen;
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % this->m_gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % this->m_gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += m_gridSize) {
        for (qreal y = top; y < rect.bottom(); y += m_gridSize) {
            points.append(QPointF(x, y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

void
SchematicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
    QMimeData const* mimeData = event->mimeData();

    if (mimeData->hasFormat(MIME_COMPONENT_TYPE)
            || mimeData ->hasFormat(MIME_PORT_PLACEMENT)) {
        m_dragOver = true;
        event->accept();
    } else {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void
SchematicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event) {
    if (m_dragOver) {
        event->accept();
    } else {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void
SchematicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {

    if (m_dragOver) {
        this->m_dragOver = false;
        event->accept();
    } else {
        QGraphicsScene::dragLeaveEvent(event);
    }
}

void
SchematicsScene::dropEvent(QGraphicsSceneDragDropEvent* event) {
    // TODO find a proper way to scale the scene and the viewport when adding items
    // TODO refactor into less ugly code

    QMimeData const* mimeData = event->mimeData();
    QPoint dropPosition = event->scenePos().toPoint();
    Document* parent = dynamic_cast<Document*>(this->parent());

    if (m_dragOver) {
        if(mimeData->hasFormat(MIME_COMPONENT_TYPE)){
        QString path = mimeData->text();

        parent->addComponent(path, dropPosition);
        } else if(mimeData->hasFormat(MIME_PORT_PLACEMENT)){

            if(QString(mimeData->data(MIME_PORT_PLACEMENT)) == "Input"){
                parent->addInputPort(mimeData->text(), dropPosition);
            } else {
                parent->addOutputPort(mimeData->text(), dropPosition);
            }
        }
        event->accept();
        this->update(); // TODO better emit this->changed?
    } else {
        QGraphicsScene::dropEvent(event);
    }
    this->m_dragOver = false;
}

void
SchematicsScene::addItem(QGraphicsItem* item) {
    QGraphicsScene::addItem(item);
}
