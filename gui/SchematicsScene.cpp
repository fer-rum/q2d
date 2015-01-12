#include "SchematicsScene.h"

#include "../Document.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <QtDebug>
#include <qt5/QtSvg/QGraphicsSvgItem>

using namespace q2d::gui;

SchematicsScene::SchematicsScene(Document* parent)
    : QGraphicsScene(parent) {

    this->addLine(0, -100, 0, 100);
    this->addLine(-100, 0, 100, 0);
}

void
SchematicsScene::drawBackground(QPainter *painter, const QRectF &rect) {

    // TODO read behaviour from settings
    QPen pen;
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % this->gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % this->gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += gridSize){
        for (qreal y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

void
SchematicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    QMimeData const * mimeData = event->mimeData();
    if(mimeData->hasText()){
        this->dragOver = true;
        event->setAccepted(true);
    } else {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void
SchematicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event){
    if(this->dragOver){
        event->setAccepted(true);
    } else {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void
SchematicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent* event){
    this->dragOver = false;
    QGraphicsScene::dragLeaveEvent(event);
}

void
SchematicsScene::dropEvent(QGraphicsSceneDragDropEvent* event){

    // TODO find a proper way to scale the scene and the viewport when adding items

    this->dragOver = false;

    QMimeData const * mimeData = event->mimeData();
    if(mimeData->hasText()){

        QString path = mimeData->text();
        QPoint dropPosition = event->scenePos().toPoint();

        dynamic_cast<Document*>(this->parent())->addComponent(path, dropPosition);
        this->update(); // TODO better emit this->changed?
    } else {
        QGraphicsScene::dropEvent(event);
    }
}
