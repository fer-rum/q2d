#include "PortGraphicsItem.h"

#include "../Constants.h"
#include "../Document.h"
#include "ComponentGraphicsItem.h"
#include "SchematicsScene.h"

#include <QApplication>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::constants;

int PortGraphicsItem::DIAMETER = 8;
int PortGraphicsItem::RADIUS = DIAMETER / 2;
QPointF PortGraphicsItem::CENTER_OFFSET = QPointF(RADIUS, RADIUS);

QPen PortGraphicsItem::PEN_INPUT_PORT  = QPen(Qt::darkGreen);
QPen PortGraphicsItem::PEN_IN_OUT_PORT = QPen(Qt::darkYellow);
QPen PortGraphicsItem::PEN_OUTPUT_PORT = QPen(Qt::darkRed);
QPen PortGraphicsItem::PEN_UNDEFINED_PORT = QPen(Qt::darkGray);
QPen PortGraphicsItem::PEN_HOVER_PORT = QPen(Qt::darkCyan);


QBrush PortGraphicsItem::BRUSH_INPUT_PORT  = QBrush(Qt::green);
QBrush PortGraphicsItem::BRUSH_IN_OUT_PORT = QBrush(Qt::yellow);
QBrush PortGraphicsItem::BRUSH_OUTPUT_PORT = QBrush(Qt::red);
QBrush PortGraphicsItem::BRUSH_UNDEFINED_PORT = QBrush(Qt::gray);
QBrush PortGraphicsItem::BRUSH_HOVER_PORT = QBrush(Qt::cyan);

bool PortGraphicsItem::m_wireDrawingMode = false;
QGraphicsLineItem*  PortGraphicsItem::m_wireDrawingLineItem = nullptr;
QPointF PortGraphicsItem::m_wireDrawingStart = QPoint();
QPointF PortGraphicsItem::m_wireDrawingEnd = QPoint();
QLineF* PortGraphicsItem::m_wireDrawingLine = nullptr;

/**
 * @brief PortGraphicsItem::PortGraphicsItem
 * The item will automatically be added to the scene, its parent belongs to.
 *
 * @param text
 * @param relativeCenterPosition is the center position of this instance
 * in coordinates relative to the the center of its parent.
 * @param direction
 * @param parent
 */
PortGraphicsItem::PortGraphicsItem(
        QPoint relativeCenterPosition,
        model::PortDirection direction,
        ComponentGraphicsItem *parent)
    : SchematicsSceneChild(parent->SchematicsSceneChild::scene(),
                           parent) {
    /* TODO: known quasi-bug
     * Passing an anonymous new QGraphicsEllipseItem directly into the constructor
     * of the SchematicsSceneChild leads to a SIGSEGV.
     *
     * I have as for now no idea why…
     */

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(parent->SchematicsSceneChild::scene());

    QAbstractGraphicsShapeItem* newActual = new QGraphicsEllipseItem(0, 0, DIAMETER, DIAMETER, this);
    Q_CHECK_PTR(newActual);

    m_direction = direction;
    // select the Pen and Brush based on the Port direction
    switch(direction){
    case model::PortDirection::IN:
        this->m_defaultPen = PEN_INPUT_PORT;
        this->m_defaultBrush = BRUSH_INPUT_PORT;
        break;
    case model::PortDirection::IN_OUT:
        this->m_defaultPen = PEN_IN_OUT_PORT;
        this->m_defaultBrush = BRUSH_IN_OUT_PORT;
        break;
    case model::PortDirection::OUT:
        this->m_defaultPen = PEN_OUTPUT_PORT;
        this->m_defaultBrush = BRUSH_OUTPUT_PORT;
        break;
    default:
        this->m_defaultPen = PEN_UNDEFINED_PORT;
        this->m_defaultBrush = BRUSH_UNDEFINED_PORT;
        break;
    }

    newActual->setPen(this->m_defaultPen);
    newActual->setBrush(this->m_defaultBrush);

    this->addActual(newActual);

    this->setPos(relativeCenterPosition.x() - RADIUS,
                  relativeCenterPosition.y() - RADIUS);

    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptDrops(true);
    Q_ASSERT(this->actual()->isVisible());
}

QString
PortGraphicsItem::specificType(){
    return q2d::model::portDirectionToQString(m_direction);
}

void
PortGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    this->actual()->setPen(PEN_HOVER_PORT);
    this->actual()->setBrush(BRUSH_HOVER_PORT);
    this->setCursor(QCursor(Qt::CrossCursor));
    event->accept();
}

void
PortGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->actual()->setPen(this->m_defaultPen);
    this->actual()->setBrush(this->m_defaultBrush);
    this->setCursor(QCursor(Qt::ArrowCursor));
    event->accept();
}

void
PortGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->scenePos();
        event->accept();
    }
}

void
PortGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    // check if we are dragging something
    if (!(event->buttons() & Qt::LeftButton)) {
             return;
    }

    if ((event->pos() - m_dragStartPosition).manhattanLength()
              < QApplication::startDragDistance()) {
             return;
    }

    // we indeed are dragging
    this->performDrag();
    event->accept();
}

/**
 * @brief PortGraphicsItem::id is a convenience function
 * @return
 */
QString
PortGraphicsItem::id() const {
    // TODO asserts
    Document* container = m_scene->document();
    return container->entry(this)->id();
}

/**
 * @brief PortGraphicsItem::performDrag initializes and performs a QDrag.
 */
void
PortGraphicsItem::performDrag() {

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    // create the payload

    QString payloadText = this->id();

    mimeData->setData(MIME_WIRE_START_POS, payloadText.toUtf8());

    drag->setMimeData(mimeData);

    m_wireDrawingMode = true;
    m_wireDrawingEnd = QPointF();
    m_wireDrawingLine = new QLineF(QPointF(), m_wireDrawingEnd);
    m_wireDrawingLineItem = m_scene->addLine(*m_wireDrawingLine);
    m_wireDrawingLineItem->setPos(this->mapToScene(RADIUS, RADIUS));
    m_wireDrawingLineItem->setVisible(true);

    // TODO the returned Action should be LINK?
    drag->exec();
}

void
PortGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    QMimeData const * mimeData = event->mimeData();

    if(mimeData->hasFormat(MIME_WIRE_START_POS)){
        this->setCursor(QCursor(Qt::CrossCursor));
        this->m_dragOver = true;
        event->accept();
    }
}

void
PortGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver && m_wireDrawingMode){
            Q_CHECK_PTR(m_wireDrawingLine);
            Q_CHECK_PTR(m_wireDrawingLineItem);
            QPointF itemCoordinate =
                    m_wireDrawingLineItem->mapFromScene(event->scenePos());
            m_wireDrawingLine->setP2(itemCoordinate);
            m_wireDrawingLineItem->setLine(*m_wireDrawingLine);
            event->accept();
            emit m_scene->sceneRectChanged(m_wireDrawingLineItem->boundingRect());
    }
}

void
PortGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver){
        m_dragOver = false;
        event->accept();
    }
}

void
PortGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent* event){

    // TODO
    // make sure target is not source
    // inform the document about the happenings via signal/slot

    if(m_dragOver && m_wireDrawingMode){
        m_dragOver = false;

        QString senderId = QString::fromUtf8(
                               event->mimeData()->data(MIME_WIRE_START_POS));
        m_scene->document()->addWire(senderId, this->id());

        event->accept();
        this->update(); // TODO better emit this->changed?
    }

    m_wireDrawingMode = false;
    this->scene()->removeItem(m_wireDrawingLineItem);
}
