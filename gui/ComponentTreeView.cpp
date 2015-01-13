#include "ComponentTreeView.h"

#include "../metamodel/ComponentDescriptor.h"
#include "../metamodel/ComponentType.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>

using namespace q2d::gui;

ComponentTreeView::ComponentTreeView(QWidget* parent) :
    QTreeView(parent) {}

void ComponentTreeView::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
             this->dragStartPosition = event->pos();
    }

    // propagate event to superclass
    QTreeView::mousePressEvent(event);
}

void ComponentTreeView::mouseMoveEvent(QMouseEvent *event) {
    // check if we are dragging something
    if (!(event->buttons() & Qt::LeftButton)) {
             return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength()
              < QApplication::startDragDistance()) {
             return;
    }

    // we should only be able to drag exactly one item
    Q_ASSERT(this->selectedIndexes().count() == 1);

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    // create the payload
    QModelIndex selected = this->selectedIndexes().first();
    QString payloadText = selected.data(ComponentDescriptorRole::HIERARCHY_NAME)
                          .toString();

    // create the pixmap for the drag operation
    QIcon icon = qvariant_cast<QIcon>(selected.data(Qt::DecorationRole));
    QPixmap iconPixmap = icon.pixmap(100);

    mimeData->setText(payloadText);
    drag->setMimeData(mimeData);
    drag->setPixmap(iconPixmap);

    drag->exec();

}
