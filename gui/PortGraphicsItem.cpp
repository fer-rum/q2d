#include "PortGraphicsItem.h"

#include "../Application.h"
#include "../Constants.h"
#include "../Document.h"
#include "../factories/GIFactory.h"
#include "ComponentGraphicsItem.h"
#include "Schematic.h"

#include <QApplication>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::constants;

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

PortGraphicsItem::PortGraphicsItem(QPointF position,
                                   DocumentEntry* relatedEntry,
                                   model::enums::PortDirection direction)
    : SchematicElement(position, relatedEntry) {
    // Ports are measured from the center, not the upper left corner

    QAbstractGraphicsShapeItem* newActual;

    m_direction = direction;
    // select the Pen and Brush based on the Port direction
    switch (direction) {
    case model::enums::PortDirection::IN:
        newActual = factories::GIFactory::createPortAdapterGI();
        this->m_defaultPen = PEN_INPUT_PORT;
        this->m_defaultBrush = BRUSH_INPUT_PORT;
        this->setAcceptDrops(true); // input ports can receive wire drops
        break;
    case model::enums::PortDirection::OUT:
        newActual = factories::GIFactory::createPortAdapteeGI();
        this->m_defaultPen = PEN_OUTPUT_PORT;
        this->m_defaultBrush = BRUSH_OUTPUT_PORT;
        this->setAcceptedMouseButtons(Qt::LeftButton); // output ports can be dragged from
        break;
    default:
        newActual = factories::GIFactory::createPortInvalidGI();
        this->m_defaultPen = PEN_UNDEFINED_PORT;
        this->m_defaultBrush = BRUSH_UNDEFINED_PORT;
        break;
    }
    Q_CHECK_PTR(newActual);

    newActual->setPen(this->m_defaultPen);
    newActual->setBrush(this->m_defaultBrush);

    this->addActual(newActual);

    newActual->setAcceptHoverEvents(true);
    Q_ASSERT(this->actual()->isVisible());
}

QPointF
PortGraphicsItem::pos() const {
    return QGraphicsItem::pos();
}

/**
 * @brief PortGraphicsItem::specificType
 * The specific sub-type of a port is its direction.
 * @return The PortDirection as string.
 */
QString
PortGraphicsItem::specificType() {
    return q2d::model::enums::PortDirectionToString(m_direction);
}

void
PortGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    this->actual()->setPen(PEN_HOVER_PORT);
    this->actual()->setBrush(BRUSH_HOVER_PORT);
    this->setCursor(QCursor(Qt::CrossCursor));
    event->accept();
}

void
PortGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    this->actual()->setPen(this->m_defaultPen);
    this->actual()->setBrush(this->m_defaultBrush);
    this->setCursor(QCursor(Qt::ArrowCursor));
    event->accept();
}

void
PortGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
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
 * @brief PortGraphicsItem::performDrag initializes and performs a QDrag.
 */
void
PortGraphicsItem::performDrag() {

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();

    // create the payload

    QString payloadText = this->id();

    mimeData->setData(MIME_WIRE_START_POS, payloadText.toUtf8());

    drag->setMimeData(mimeData);

    m_wireDrawingMode = true;
    m_wireDrawingEnd = QPointF();
    m_wireDrawingLine = new QLineF(QPointF(), m_wireDrawingEnd);
    m_wireDrawingLineItem = m_scene->addLine(*m_wireDrawingLine);
    m_wireDrawingLineItem->setPos(this->mapToScene(PORT_RADIUS, PORT_RADIUS));
    m_wireDrawingLineItem->setVisible(true);

    // TODO the returned Action should be LINK?
    drag->exec();
}

void
PortGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
    QMimeData const* mimeData = event->mimeData();

    if (mimeData->hasFormat(MIME_WIRE_START_POS)) {
        this->setCursor(QCursor(Qt::CrossCursor));
        this->m_dragOver = true;
        event->accept();
    }
}

void
PortGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent* event) {

    if (m_dragOver && m_wireDrawingMode) {
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
PortGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {

    if (m_dragOver) {
        m_dragOver = false;
        event->accept();
    }
}

void PortGraphicsItem::slot_drawConnected()
{
    QAbstractGraphicsShapeItem* newActual;
    switch(m_direction){
    case model::enums::PortDirection::IN:
        newActual = factories::GIFactory::createPortAdapteeGI();
        break;
    case model::enums::PortDirection::OUT:
       newActual = factories::GIFactory::createPortAdapterGI();
        break;
    default: // should not happen
        Q_ASSERT(false);
    }
    newActual->setBrush(m_defaultBrush);
    newActual->setPen(m_defaultPen);
    this->addActual(newActual);
}

void
PortGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent* event) {

    // TODO
    // make sure target is not source
    // better inform the document about the happenings via signal/slot

    if (m_dragOver && m_wireDrawingMode) {
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

ModulePortGI::ModulePortGI(
        QPointF relativeCenterPosition,
        DocumentEntry* relatedEntry,
        model::enums::PortDirection direction)
    : PortGraphicsItem(relativeCenterPosition, relatedEntry, model::enums::invert(direction)) {

    int moveX;
    int moveY;
    QGraphicsSvgItem* decal;
    switch(direction) {
    case model::enums::PortDirection::OUT :
        decal = new QGraphicsSvgItem(":/icons/ressources/icons/outside_port_out.svg", this);
        moveX = 0;
        moveY = -decal->boundingRect().height()/2;
        break;
    case model::enums::PortDirection::IN :
        decal = new QGraphicsSvgItem(":/icons/ressources/icons/outside_port_in.svg", this);
        moveX = -decal->boundingRect().width();
        moveY = -decal->boundingRect().height()/2;
        break;
    default : // should not happen
        Q_ASSERT(false);
    }
    this->addActual(decal);
    Q_ASSERT(decal->parentItem() == this);
    decal->moveBy(moveX, moveY);
    this->recalculateBoundingRect();

    // for debugging
    this->setFlag(QGraphicsItem::ItemIsSelectable);

}

/**
 * @brief ModulePortGI::specificType is the PortDirection as viewed from outside the module.
 * Therefore, the internal value is to be reversed.
 * So an input port will return <i>in</i> and an output port will return <i>out</i>.
 * @return The (inverted) PortDirection as String
 */
QString
ModulePortGI::specificType() {
    return model::enums::PortDirectionToString(model::enums::invert(m_direction));
}
