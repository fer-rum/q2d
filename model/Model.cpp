#include "Model.h"

#include "../Document.h"

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

    this->name = parent->text();
    this->components = QList<Component*>();
    this->conductors = QList<Conductor*>();
    this->outsidePorts = QList<Port*>();
}

void
Model::addComponent(Component* toAdd){
    Q_CHECK_PTR(toAdd);
    this->components.append(toAdd);
}

void
Model::connect(Node* start, Node* end){
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    Conductor* toAdd = new Conductor(start, end, this);
    start->addDrivenElement(toAdd);
    end->addDriver(toAdd);

    this->conductors.append(toAdd);
}
