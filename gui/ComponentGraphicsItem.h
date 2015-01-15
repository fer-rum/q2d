#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include <QGraphicsSvgItem>

namespace q2d {
namespace gui {

    // forward declaration
    class SchematicsScene;

class ComponentGraphicsItem : public QGraphicsSvgItem
{
    Q_OBJECT

private:
    SchematicsScene* scene;

public:
    explicit ComponentGraphicsItem(QString file, SchematicsScene *scene, QPoint position);

signals:

public slots:

};

} // namespace gui
} // namespce q2d

#endif // COMPONENTGRAPHICSITEM_H
