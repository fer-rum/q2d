#include "Component.h"

using namespace q2d::model;

Component::Component(QString name, Model* internalModel) : ModelElement(name) {
    this->internalModel = internalModel;
}

/**
 * @brief Component::createPort creates a new port with the given parameters
 * and adds it to the component.
 *
 * @param name
 * @param direction
 * @return the newly created port
 */
Port*
Component::createPort(QString name, PortDirection direction){
    Port* newPort = new Port(name, direction);
    this->ports.append(newPort);
    return newPort;
}
