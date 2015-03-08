#include "../Document.h"
#include "../Enumerations.h"

#include "Component.h"
#include "Conductor.h"
#include "Model.h"
#include "Node.h"
#include "Port.h"

#include <QtDebug>

using namespace q2d::model;

/**
 * @brief Model::Model
 * The model will automatically fetch its name from the parent Document.
 *
 * @param parent must not be null
 */
Model::Model(Document* parent)
    : QObject(parent), m_components(), m_conductors(), m_inputPorts(), m_outputPorts() {

    Q_CHECK_PTR(parent);

    m_name = parent->text();

    qDebug() << "Model: creating new model " << m_name << "";
}

void
Model::addComponent(Component* toAdd) {
    Q_CHECK_PTR(toAdd);
    this->m_components.append(toAdd);

    qDebug() << "Model: Added component of type \"" << toAdd->descriptor()->text() << "\"";
}

void
Model::addInputPort(ModulePort* inputPort) {
    Q_CHECK_PTR(inputPort);
    Q_ASSERT(inputPort->direction() == enums::PortDirection::OUT);
    m_inputPorts.append(inputPort);
}

void
Model::addOutputPort(ModulePort* outputPort) {
    Q_CHECK_PTR(outputPort);
    Q_ASSERT(outputPort->direction() == enums::PortDirection::IN);
    m_outputPorts.append(outputPort);
}


void
Model::addConductor(Conductor* conductor) {
    m_conductors.append(conductor);
}
