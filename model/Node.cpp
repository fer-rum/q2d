#include "Node.h"

using namespace q2d::model;

Node::Node(QString name) : ModelElement(name) {}

Port::Port(PortDirection, QString name) : Node(name) {
    this->direction = direction;
}
