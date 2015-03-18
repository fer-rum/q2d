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

class SchematicsView :
        public QGraphicsView {
    Q_OBJECT
protected:

    // override for custom handling
    // TODO need to forward to scene?
//    virtual void dragEnterEvent(QDragEnterEvent* event);
//    virtual void dragMoveEvent(QDragMoveEvent* event);
//    virtual void dragLeaveEvent(QDragLeaveEvent* event);
//    virtual void dropEvent(QDropEvent *event);

public:
    explicit SchematicsView(QWidget* parent = nullptr);

    void resizeEvent( QResizeEvent* e )
    {
    double w = ( e->size().width());
    double h = ( e->size().height());
    QGraphicsView::resizeEvent(e);
    this->scene()->setSceneRect(0, 0, w, h);
    }

};


} // namespace gui
} // namespace q2d


#endif // SCHEMATICSVIEW_H
