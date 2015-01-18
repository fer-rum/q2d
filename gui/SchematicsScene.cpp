#include "SchematicsScene.h"

#include "../Constants.h"
#include "../Document.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <QtDebug>
#include <qt5/QtSvg/QGraphicsSvgItem>

using namespace q2d::gui;
using namespace q2d::constants;

SchematicsScene::SchematicsScene(Document* parent)
    : QGraphicsScene(parent) {

// for debug purposes
//    this->addLine(0, -100, 0, 100);
//    this->addLine(-100, 0, 100, 0);
}

void
SchematicsScene::drawBackground(QPainter *painter, const QRectF &rect) {

    // TODO read behaviour from settings
    QPen pen;
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % this->m_gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % this->m_gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += m_gridSize){
        for (qreal y = top; y < rect.bottom(); y += m_gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

void
SchematicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    QMimeData const * mimeData = event->mimeData();

    if(mimeData->hasFormat(MIME_COMPONENT_TYPE)){
        this->m_dragOver = true;
        event->accept();
    } else {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void
SchematicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event){
    if(this->m_dragOver){
        if(this->wireDrawingMode()){
            this->m_wireDrawingLine->line().setP2(event->scenePos());
            qDebug() << "Relocated wire end";
        }
        event->accept();
    } else {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void
SchematicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver){
        this->m_dragOver = false;
    }

    QGraphicsScene::dragLeaveEvent(event);
}

void
SchematicsScene::dropEvent(QGraphicsSceneDragDropEvent* event){

    if(!m_dragOver){
        QGraphicsScene::dropEvent(event);
        return;
    }
    // TODO find a proper way to scale the scene and the viewport when adding items

    this->m_dragOver = false;

    if(this->m_wireDrawingMode){
        QGraphicsScene::dropEvent(event);
        return;
    }

    QMimeData const * mimeData = event->mimeData();
    if(mimeData->hasFormat(MIME_COMPONENT_TYPE)){
        event->setAccepted(true);

        QString path = mimeData->text();
        QPoint dropPosition = event->scenePos().toPoint();

        dynamic_cast<Document*>(this->parent())->addComponent(path, dropPosition);
        this->update(); // TODO better emit this->changed?
    } else {
        QGraphicsScene::dropEvent(event);
    }
}

bool
SchematicsScene::wireDrawingMode() const {
    return this->m_wireDrawingMode;
}

void
SchematicsScene::setWireDrawingMode(bool mode, QPointF* origin){
    this->m_wireDrawingMode = mode;
    if(mode){
        this->m_wireDrawingLine = new QGraphicsLineItem(QLine());
        this->m_wireDrawingLine->line().setP1(*origin);
        this->addItem(this->m_wireDrawingLine);
        this->m_wireDrawingLine->setVisible(true);
    } else {
        this->removeItem(this->m_wireDrawingLine);
        delete this->m_wireDrawingLine;
    }
}
