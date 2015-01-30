#include "ComponentTreeView.h"

#include "Constants.h"
#include "Enumerations.h"
#include "../metamodel/ComponentDescriptor.h"
#include "../metamodel/ComponentType.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::constants;


QSize ComponentTreeView::ICON_SIZE = QSize(48, 48);

ComponentTreeView::ComponentTreeView(QWidget* parent) :
    QTreeView(parent) {}

void
ComponentTreeView::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
             this->dragStartPosition = event->pos();
    }

    // propagate event to superclass
    QTreeView::mousePressEvent(event);
}

void
ComponentTreeView::performDrag() {
    // we should only be able to drag exactly one item
    Q_ASSERT(this->selectedIndexes().count() == 1);

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    // create the payload
    QModelIndex selected = this->selectedIndexes().first();
    QString payloadText = selected.data(ComponentDescriptorRole::HIERARCHY_NAME)
                          .toString();

    // create the pixmap for the drag operation
    QIcon icon = qvariant_cast<QIcon>(selected.data(Qt::DecorationRole));

    // getting the size is a hack for now
    // there should be a more proper way to implement it better
    QPixmap iconPixmap = icon.pixmap(ICON_SIZE);

    mimeData->setData(MIME_COMPONENT_TYPE, payloadText.toUtf8());
    mimeData->setText(payloadText);
    drag->setMimeData(mimeData);
    drag->setPixmap(iconPixmap);

    drag->exec();
}

void
ComponentTreeView::mouseMoveEvent(QMouseEvent *event) {
    // check if we are dragging something
    if (event->buttons() & Qt::LeftButton) {

        if ((event->pos() - dragStartPosition).manhattanLength()
                >= QApplication::startDragDistance()) {
            this->performDrag();
        }
    } else { // propagate event to superclass
        QTreeView::mouseMoveEvent(event);
    }
}
