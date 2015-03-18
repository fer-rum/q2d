#include "../DocumentEntry.h"

#include "Constants.h"
#include "JsonHelpers.h"
#include "Schematic.h"
#include "SchematicElement.h"

// debug
#include <QtDebug>
#include "../Util.h"

using namespace q2d::gui;
using namespace q2d::constants;

const QJsonObject SchematicElement::EMPTY_JSON = QJsonObject();

SchematicElement::SchematicElement(QPointF position, q2d::DocumentEntry* relatedEntry)
    : QGraphicsObject(relatedEntry->parent() != nullptr? relatedEntry->parent()->schematicElement()
                                      : nullptr) {
    Q_CHECK_PTR(relatedEntry);
    m_relatedEntry = relatedEntry;
    m_scene = relatedEntry->scene();
    m_actuals = QList<QGraphicsItem*>();
    m_boundingRect = QRectF(0, 0, 0, 0);
    this->setPos(position);
}

Schematic*
SchematicElement::scene() const {
    Q_CHECK_PTR(m_scene);
    return m_scene;
}

void
SchematicElement::addActual(QGraphicsItem* actual) {
    m_actuals.append(actual);
    actual->setParentItem(this);
    this->recalculateBoundingRect();

}

/**
 * @brief SchematicsSceneChild::actual gives the actual element
 * under the assumption that there is only exactly one item
 * in the list of actuals.
 * If there are more, the first one will be returned
 * @return
 */
QAbstractGraphicsShapeItem*
SchematicElement::actual() const {
    Q_ASSERT(!m_actuals.isEmpty());
    QAbstractGraphicsShapeItem* result =
        dynamic_cast<QAbstractGraphicsShapeItem*>(m_actuals.first());
    Q_CHECK_PTR(result);
    return result;
}

/**
 * @brief SchematicsSceneChild::recalculateBoundingRect
 * calculates the minimal bounding rectangle from all items
 * contained in m_actual.
 *
 * The resulting bounding rectangle is cached
 * in m_boundingRect and can be aquired via boundingRect().
 */
void
SchematicElement::recalculateBoundingRect() {

    // the trivial case
    if (m_actuals.isEmpty()) {
        this->setBoundingRect(QRect(0, 0, 0, 0));
    }

    qreal minX, maxX, minY, maxY;

    // start with some value
    // not using (0,0) because items may all be in negative X and Y
    QGraphicsItem* first = m_actuals.first();
    QRectF currentRect = first->boundingRect();

    minX = currentRect.x() + first->pos().x();
    minY = currentRect.y() + first->pos().y();

    maxX = minX + currentRect.width();
    maxY = minY + currentRect.height();

    for (QGraphicsItem * actual : m_actuals) {
        currentRect = actual->boundingRect();

        qreal tempMinX = currentRect.x() + actual->pos().x();
        qreal tempMinY = currentRect.y() + actual->pos().y();

        qreal tempMaxX = tempMinX + currentRect.width();
        qreal tempMaxY = tempMinY + currentRect.height();

        minX = tempMinX < minX ? tempMinX : minX;
        minY = tempMinY < minY ? tempMinY : minY;
        maxX = tempMaxX > maxX ? tempMaxX : maxX;
        maxY = tempMaxY > maxY ? tempMaxY : maxY;
    }

    this->prepareGeometryChange();
    this->setBoundingRect(QRectF(minX, minY, maxX - minX, maxY - minY));
}

void
SchematicElement::paint(QPainter* painter,
                            const QStyleOptionGraphicsItem* option,
                            QWidget* widget) {

    if (m_actuals.isEmpty()) {
        return;
    }

    for (QGraphicsItem * actual : m_actuals) {
        actual->paint(painter, option, widget);
    }
}
QString
SchematicElement::id() const {
    return m_relatedEntry->id();
}
