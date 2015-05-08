#ifndef SCHEMATICSSCENECHILD_H
#define SCHEMATICSSCENECHILD_H

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsObject>
#include <QGraphicsSvgItem>
#include <QJsonObject>
#include <QList>

namespace q2d {

class DocumentEntry;

namespace gui {

class Schematic;

// TODO maybe merge the actuals into a QGraphicsItemGroup?

/**
 * @brief The SchematicsElement class encapsules all functionality
 * shared by all items that might be used in SchematicsScene-instances.
 * This is mainly to reduce coding work and code duplication.
 * It also narrows down the type of the scene.
 *
 * If the given related DocumentEntry has a parent, the parents schematic element will be used
 * as parent for the newly created instance.
 *
 * SchematicsSceneChild-instances are composed out of an "actuals" list
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
class SchematicElement
        : public QGraphicsObject {

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

    DocumentEntry* m_relatedEntry;
    Schematic* m_scene;

    void setBoundingRect(QRectF rect) {
        m_boundingRect = rect;
    }

    virtual void recalculateBoundingRect();

    void addActual(QGraphicsItem* actual);

    void clearActuals();

    int countActuals() const {
        return m_actuals.count();
    }
    QAbstractGraphicsShapeItem* actual() const;
    QList<QGraphicsItem*> actuals() const {
        return m_actuals;
    }

public:
    SchematicElement(QPointF position, DocumentEntry* relatedEntry);

    Schematic* scene() const;

    /**
     * @brief id is a convenience shortcut for querying the id of the related document entry
     * @return
     */
    QString id() const; // TODO fullID vs local ID

    // for JSON generation
    // you must/may want to override these.
    virtual QString specificType() = 0;
    virtual QJsonObject additionalJson() {
        return EMPTY_JSON;
    }

    /**
     * @brief savePosition determines whether the position of the element on the schematic
     * should be saved or will be determined automatically.
     * If not overridden, this returns true by default.
     * @return
     */
    virtual bool savePosition() const {
        return true;
    }

    // necessary overrides
    virtual QRectF boundingRect() const override {
        return m_boundingRect;
    }

    virtual void paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = nullptr) override;
};

/**
 * @brief The ParentSchematicElement class is a specialization for schematic elements
 * that are parents to other schematic elements
 */
class ParentSchematicElement
        : public SchematicElement {
    Q_OBJECT
protected:
    explicit ParentSchematicElement(QPointF position, DocumentEntry* relatedEntry)
        : SchematicElement(position, relatedEntry) {}
signals:
    void signal_posChanged();
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSSCENECHILD_H
