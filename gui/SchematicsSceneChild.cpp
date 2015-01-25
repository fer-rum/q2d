#include "SchematicsSceneChild.h"
#include "SchematicsScene.h"

using namespace q2d::gui;

SchematicsSceneChild::SchematicsSceneChild(SchematicsScene *scene, SchematicsSceneChild* parent)
    : QGraphicsObject(parent) {
    Q_CHECK_PTR(scene);
    m_scene = scene;
    m_actuals = QList<QGraphicsItem*>();
    m_boundingRect = QRectF(0,0,0,0);
}

SchematicsSceneChild::SchematicsSceneChild(SchematicsScene *scene,
                                           QGraphicsItem* actual,
                                           SchematicsSceneChild* parent)
    : SchematicsSceneChild(scene, parent) {
    Q_CHECK_PTR(actual);
    this->addActual(actual);
}

SchematicsScene*
SchematicsSceneChild::scene() const {
    Q_CHECK_PTR(m_scene);
    return m_scene;
}

void
SchematicsSceneChild::addActual(QGraphicsItem *actual){
    m_actuals.append(actual);
    this->recalculateBoundingRect();
}

QAbstractGraphicsShapeItem*
SchematicsSceneChild::actual() const {
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
SchematicsSceneChild::recalculateBoundingRect(){

    // the trivial case
    if(m_actuals.isEmpty()){ this->setBoundingRect(QRect(0,0,0,0)); }

    qreal minX, maxX, minY, maxY;

    // start with some value
    // not using (0,0) because items may all be in negative X and Y
    QRectF currentRect = m_actuals.first()->boundingRect();

    minX = currentRect.x();
    minY = currentRect.y();

    maxX = minX + currentRect.width();
    maxY = minY + currentRect.height();

    for(QGraphicsItem* actual : m_actuals){
        currentRect = actual->boundingRect();

        qreal tempMinX = currentRect.x();
        qreal tempMinY = currentRect.y();

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
SchematicsSceneChild::paint(QPainter* painter,
                            const QStyleOptionGraphicsItem* option,
                            QWidget* widget){

    if(m_actuals.isEmpty()){ return; }

    for(QGraphicsItem* actual : m_actuals){
        actual->paint(painter, option, widget);
    }
}
