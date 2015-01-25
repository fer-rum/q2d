#ifndef SCHEMATICSSCENECHILD_H
#define SCHEMATICSSCENECHILD_H

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsObject>
#include <QGraphicsSvgItem>
#include <QList>

namespace q2d {
namespace gui {

class SchematicsScene;

// TODO maybe merge the actuals into a QGraphicsItemGroup?

/**
 * @brief The SchematicsSceneChild class encapsules all functionality
 * shared by all items that might be used in SchematicsScene-instances.
 * This is mainly to reduce coding work and code duplication.
 * It also narrows down the type of the scene.
 *
 * SchematicsSceneChild-instances are composed out of an "actuals" List
 * of QGraphicsItems that may even be empty.
 *
 * Per default paint calls are directed to this actual and the boundingRect is
 * derived from it.
 */
class SchematicsSceneChild : public QGraphicsObject {

private:
    QList<QGraphicsItem*> m_actuals;

    /**
     * @brief m_boundingRect caches the bounding rectangle.
     * It should be recalculated if m_actuals changes.
     */
    QRectF m_boundingRect;

protected:
    SchematicsScene* m_scene;

    void setBoundingRect(QRectF rect)
    { m_boundingRect = rect; }

    virtual void recalculateBoundingRect();

    void addActual(QGraphicsItem* actual);

    void clearActuals()
    { m_actuals.clear(); }

    int countActuals() const
    { return m_actuals.count(); }

    QAbstractGraphicsShapeItem* actual() const;

    QList<QGraphicsItem*> actuals() const
    { return m_actuals; }
    // TODO add overrides as needed

public:
    SchematicsSceneChild(SchematicsScene* scene,
                         QGraphicsItem* actual,
                         SchematicsSceneChild* parent = nullptr);
    SchematicsSceneChild(SchematicsScene* scene,
                         SchematicsSceneChild* parent = nullptr);

    SchematicsScene* scene() const;

    // necessary overrides
    virtual QRectF boundingRect() const
    { return m_boundingRect; }

    virtual void paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = nullptr);
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSSCENECHILD_H
