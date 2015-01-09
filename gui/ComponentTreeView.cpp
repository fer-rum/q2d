#include "ComponentTreeView.h"

#include "../ComponentDescriptor.h"

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
    if (!(event->buttons() & Qt::LeftButton)) {
             return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength()
              < QApplication::startDragDistance()) {
             return;
    }

    Q_ASSERT(!this->selectedIndexes().isEmpty());

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    QModelIndex selected = this->selectedIndexes().first();
    QString symbolPath = selected.data(ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE).toString();
    QIcon icon = qvariant_cast<QIcon>(selected.data(Qt::DecorationRole));
    QPixmap iconPixmap = icon.pixmap(100);

    mimeData->setText(symbolPath);
    drag->setMimeData(mimeData);
    drag->setPixmap(iconPixmap);

    drag->exec();

}
