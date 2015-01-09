#ifndef SCHEMATICSVIEW_H
#define SCHEMATICSVIEW_H

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QGraphicsView>
#include <QWidget>

namespace q2d {
namespace gui {

class SchematicsView : public QGraphicsView {
protected:

    // override for custom handling
    // TODO need to forward to scene?
//    virtual void dragEnterEvent(QDragEnterEvent* event);
//    virtual void dragMoveEvent(QDragMoveEvent* event);
//    virtual void dragLeaveEvent(QDragLeaveEvent* event);
//    virtual void dropEvent(QDropEvent *event);

public:
    explicit SchematicsView(QWidget* parent = nullptr);

};

} // namespace gui
} // namespace q2d


#endif // SCHEMATICSVIEW_H
