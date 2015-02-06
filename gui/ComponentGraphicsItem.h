#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include "Constants.h"
#include "SchematicsSceneChild.h"
#include <QGraphicsSvgItem>

namespace q2d {

// forward declaration
namespace metamodel {
class ComponentDescriptor;
}

namespace gui {

class ComponentGraphicsItem : public SchematicsSceneChild {
    Q_OBJECT
private:
    QGraphicsSvgItem* m_actuals; // the actually item that gets displayed
    metamodel::ComponentDescriptor* m_type;

protected:
    virtual QString specificType();

public:
    explicit ComponentGraphicsItem(metamodel::ComponentDescriptor* type, SchematicsScene* scene,
                                   QPointF position);

signals:

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
