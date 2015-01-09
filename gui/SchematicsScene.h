#ifndef SCHEMATICSSCENE_H
#define SCHEMATICSSCENE_H

#include <QGraphicsScene>
#include <QObject>

namespace q2d {
namespace gui {


class SchematicsScene
    : public QGraphicsScene {
    Q_OBJECT
private:
    bool dragOver = false;
    int gridSize = 20;
public:
    explicit SchematicsScene(QObject* parent = 0);
//    virtual ~SchematicsScene();

    // cosmetic overrides
    void drawBackground(QPainter *painter, const QRectF &rect);

    // overrides for custom handling
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSSCENE_H
