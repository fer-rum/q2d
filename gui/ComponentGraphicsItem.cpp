
#include "../DocumentEntry.h"
#include "../factories/GIFactory.h"
#include "../metamodel/ComponentDescriptor.h"
#include "../metamodel/PortDescriptor.h"
#include "../model/ModelElement.h"
#include "../model/Component.h"
#include "ComponentGraphicsItem.h"
#include "PortGraphicsItem.h"
#include "Schematic.h"

using namespace q2d::gui;
using namespace q2d::metamodel;

ComponentGraphicsItem::ComponentGraphicsItem(
    QPointF position,
    DocumentEntry* relatedEntry,
    metamodel::ComponentDescriptor* type)
    : ParentSchematicElement(position, relatedEntry) {
    Q_CHECK_PTR(type);

    m_type = type;
    if (!type->symbolPath().isEmpty()) {
        this->addActual(new QGraphicsSvgItem(type->symbolPath()));
    } else {
        QGraphicsItem* actual = factories::GIFactory::createComponentGI(type);
        m_scene->addItem(actual); // TODO duplicate?
        this->addActual(actual);
        actual->setVisible(true); // TODO duplicate?

        // NOTE debug
        for (QGraphicsItem * child : actual->childItems()) {
            Q_ASSERT(child->isVisible());
        }
    }
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges); // needed to detect movement
}

/**
 * @brief ComponentGraphicsItem::specificType
 * @return the hierarchy name of the type the component was instantiated from.
 */
QString
ComponentGraphicsItem::specificType() {
    return m_type->hierarchyName();
}

void
ComponentGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {

    model::Component* component = dynamic_cast<model::Component*>(m_relatedEntry->modelElement());

    emit this->scene()->signal_componentDetailRequested(component);
    event->accept();
}

QVariant
ComponentGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        emit signal_posChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}
