#ifndef SCHEMATICSSCENE_H
#define SCHEMATICSSCENE_H

#include "../ComponentFactory.h"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QObject>

namespace q2d {

    // forward declaration
    class Document;

namespace gui {


class SchematicsScene
    : public QGraphicsScene {
    Q_OBJECT
private:
    bool    m_dragOver          = false;
    bool    m_wireDrawingMode   = false;
    QGraphicsLineItem*  m_wireDrawingLine;
    int     m_gridSize          = 20; // TODO read from Settings

public:
    explicit SchematicsScene(Document* parent);
//    virtual ~SchematicsScene();

    bool wireDrawingMode() const;
    void setWireDrawingMode(bool mode, QPointF* origin = nullptr);

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
