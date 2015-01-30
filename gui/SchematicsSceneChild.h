#ifndef SCHEMATICSSCENECHILD_H
#define SCHEMATICSSCENECHILD_H

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsObject>
#include <QGraphicsSvgItem>
#include <QJsonObject>
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
 *
 * JSON generation:
 * Some methods needed for generation JSON have to be overridden by the subclass.
 * <ul>
 * <li>specificType() is more detailed wit regard to port direction,
 * component type etc. Also see the concrete implementations documentation.</li>
 * <li>additionalJson() may be overridden if there are some more specific settings
 * to be stored while saving.</li>
 * </ul>
 */
class SchematicsSceneChild : public QGraphicsObject {

    // TODO maybe cache and update the generated Json,
    // it may also be used as better dragging text or as tooltip?

private:
    QList<QGraphicsItem*> m_actuals;

    /**
     * @brief m_boundingRect caches the bounding rectangle.
     * It should be recalculated if m_actuals changes.
     */
    QRectF m_boundingRect;

protected:
    static const QJsonObject EMPTY_JSON;

    SchematicsScene* m_scene;

    void setBoundingRect(QRectF rect)
    { m_boundingRect = rect; }

    virtual void recalculateBoundingRect();

    void addActual(QGraphicsItem* actual);

    void clearActuals(){ m_actuals.clear(); }
    int countActuals() const { return m_actuals.count(); }
    QAbstractGraphicsShapeItem* actual() const;
    QList<QGraphicsItem*> actuals() const { return m_actuals; }
    // TODO add overrides as needed

public:
    SchematicsSceneChild(SchematicsScene* scene,
                         QGraphicsItem* actual,
                         SchematicsSceneChild* parent = nullptr);
    SchematicsSceneChild(SchematicsScene* scene,
                         SchematicsSceneChild* parent = nullptr);

    SchematicsScene* scene() const;
    // for JSON generation
    // you must/may want to override these.
    virtual QString specificType() = 0;
    virtual QJsonObject additionalJson()
    { return EMPTY_JSON; }

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
