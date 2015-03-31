#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include "Constants.h"
#include "SchematicElement.h"
#include <QGraphicsSvgItem>

#include <QtDebug>

namespace q2d {

// forward declaration
namespace metamodel {
class ComponentDescriptor;
}

namespace gui {

class ComponentGraphicsItem : public ParentSchematicElement {
    Q_OBJECT
private:
    metamodel::ComponentDescriptor* m_descriptor;

protected:
    virtual QString specificType();

public:
    explicit ComponentGraphicsItem(
        QPointF position,
        DocumentEntry* relatedEntry,
        metamodel::ComponentDescriptor* descriptor);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    metamodel::ComponentDescriptor* descriptor() const {
        return m_descriptor;
    }

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
