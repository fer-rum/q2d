#ifndef SCHEMATICSSCENE_H
#define SCHEMATICSSCENE_H

#include "../ComponentFactory.h"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QObject>

namespace q2d {

// forward declaration
class Document;

namespace gui {


class Schematic
        : public QGraphicsScene {
    Q_OBJECT
private:
    bool    m_dragOver          = false;
    int     m_gridSize          = 20; // TODO read from Settings

    void handleMimePortPlacement(const QMimeData* mimeData, QPoint dropPosition);

public:
    explicit Schematic(Document* parent);
    Document* document() const;

    // cosmetic overrides
    void drawBackground(QPainter* painter, const QRectF &rect);

    // overrides for custom handling
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);

    // debug hook
    virtual void addItem(QGraphicsItem* item); // TODO specialize to SchematicElement?
//    virtual void mouseMoveEvent(QMouseEvent* event);

signals:
    void signal_mousePosChanged(int x, int y);
    void signal_componentDetailRequested(model::Component* component);
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSSCENE_H
