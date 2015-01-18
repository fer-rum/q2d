#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include <QGraphicsSvgItem>

namespace q2d {

namespace metamodel {
class ComponentType;
}

namespace gui {

    // forward declaration
    class SchematicsScene;

class ComponentGraphicsItem : public QGraphicsSvgItem
{
    Q_OBJECT

private:
    SchematicsScene* parentScene;

public:
    explicit ComponentGraphicsItem(metamodel::ComponentType* type, SchematicsScene *scene, QPoint position);

    SchematicsScene* scene() const;

signals:

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
