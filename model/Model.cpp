#include "../Document.h"
#include "../Enumerations.h"

#include "Component.h"
#include "Conductor.h"
#include "Model.h"
#include "ModuleInterface.h"
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
Model::addInputPort(ModuleInterface* inputPort) {
    Q_CHECK_PTR(inputPort);
    Q_ASSERT(inputPort->direction() == enums::PortDirection::IN);
    m_inputPorts.append(inputPort);
}

void
Model::addOutputPort(ModuleInterface* outputPort) {
    Q_CHECK_PTR(outputPort);
    Q_ASSERT(outputPort->direction() == enums::PortDirection::OUT);
    m_outputPorts.append(outputPort);
}


void
Model::addConductor(Conductor* conductor) {
    m_conductors.append(conductor);
}

QList<ModulePort*>
Model::outsidePorts() const {

    QList<ModulePort*> result = QList<ModulePort*>();

    for (ModuleInterface * interface : m_inputPorts) {
        result.append(interface->port());
    }

    for (ModuleInterface * interface : m_outputPorts) {
        result.append(interface->port());
    }

    return result;
}
