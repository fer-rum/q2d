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

class ComponentGraphicsItem : public SchematicElement {
    Q_OBJECT
private:
    metamodel::ComponentDescriptor* m_type;

protected:
    virtual QString specificType();

public:
    explicit ComponentGraphicsItem(
            QPointF position,
            DocumentEntry* relatedEntry,
            metamodel::ComponentDescriptor* type);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

signals:
    QVariant signal_positionChanged();

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
