#include "Model.h"

#include "../Document.h"

#include <QtDebug>

using namespace q2d::model;

/**
 * @brief Model::Model
 * The model will automatically fetch its name from the parent Document.
 *
 * @param parent must not be null
 */
Model::Model(Document* parent)
    : QObject(parent) {

    Q_CHECK_PTR(parent);

    m_name = parent->text();
    m_components = QList<Component*>();
    m_conductors = QList<Conductor*>();
    m_outsidePorts = QList<Port*>();

    qDebug() << "Model: creating new model " << m_name << "";
}

void
Model::addComponent(Component* toAdd) {
    Q_CHECK_PTR(toAdd);
    this->m_components.append(toAdd);

    qDebug() << "Model: Added component of type \"" << toAdd->descriptor()->text() << "\"";
}

Conductor*
Model::connect(Node* start, Node* end) {
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    Conductor* toAdd = new Conductor(start, end, this);
    start->addDrivenElement(toAdd);
    end->addDriver(toAdd);

    m_conductors.append(toAdd);
    return toAdd;
}
