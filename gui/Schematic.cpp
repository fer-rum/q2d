#include "Schematic.h"

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

Schematic::Schematic(Document* parent)
    : QGraphicsScene(parent) {

}

q2d::Document*
Schematic::document() const {
    return qobject_cast<Document*>(parent());
}

void
Schematic::drawBackground(QPainter* painter, const QRectF &rect) {

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
Schematic::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
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
Schematic::dragMoveEvent(QGraphicsSceneDragDropEvent* event) {
    if (m_dragOver) {
        event->accept();
    } else {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void
Schematic::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {

    if (m_dragOver) {
        this->m_dragOver = false;
        event->accept();
    } else {
        QGraphicsScene::dragLeaveEvent(event);
    }
}

void
Schematic::dropEvent(QGraphicsSceneDragDropEvent* event) {
    // TODO find a proper way to scale the scene and the viewport when adding items
    // TODO refactor into less ugly code

    QMimeData const* mimeData = event->mimeData();
    QPoint dropPosition = event->scenePos().toPoint();
    Document* parent = dynamic_cast<Document*>(this->parent());

    if (m_dragOver) {
        if (mimeData->hasFormat(MIME_COMPONENT_TYPE)) {
            QString path = mimeData->text();

            parent->addComponent(path, dropPosition);
        } else if (mimeData->hasFormat(MIME_PORT_PLACEMENT)) {
            this->handleMimePortPlacement(mimeData, dropPosition);
        }
        event->accept();
        this->update(); // TODO better emit this->changed?
    } else {
        QGraphicsScene::dropEvent(event);
    }
    this->m_dragOver = false;
}

void
Schematic::handleMimePortPlacement(const QMimeData* mimeData, QPoint dropPosition){
    model::enums::PortDirection direction =
            model::enums::StringToPortDirection(QString(mimeData->data(MIME_PORT_PLACEMENT)));

    switch(direction) {
    case model::enums::PortDirection::IN :
        this->document()->addInputPort(mimeData->text(), dropPosition);
        break;
    case model::enums::PortDirection::OUT :
        this->document()->addOutputPort(mimeData->text(), dropPosition);
        break;
    default: // should not happen
    Q_ASSERT(false);
    }
}

void
Schematic::addItem(QGraphicsItem* item) {
    QGraphicsScene::addItem(item);
}
