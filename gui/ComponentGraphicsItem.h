#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include "Constants.h"
#include "SchematicsSceneChild.h"
#include <QGraphicsSvgItem>

namespace q2d {

// forward declaration
namespace metamodel {
class ComponentType;
}

namespace gui {

class ComponentGraphicsItem : public SchematicsSceneChild {
    Q_OBJECT
private:
    QGraphicsSvgItem* m_actuals; // the actually item that gets displayed
    metamodel::ComponentType* m_type;

protected:
    virtual QString specificType();

public:
    explicit ComponentGraphicsItem(metamodel::ComponentType* type, SchematicsScene* scene,
                                   QPointF position);

signals:

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
