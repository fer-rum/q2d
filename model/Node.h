#ifndef NODE_H
#define NODE_H

#include "ModelElement.h"
#include "PortDirection.h"

#include <QList>

namespace q2d {
namespace model {

    // forward declaration
    class Component;

// TODO documentation
// TODO visitor pattern
// TODO implementation
class Node : public ModelElement {
private:
    QList<ModelElement*> drivenElements;
    ModelElement* driver;
public:
    Node(Model* parent);

    void addDriver(ModelElement* driver);
    void addDrivenElement(ModelElement* drivenElement);
};

// TODO visitor-pattern
// TODO documentation
class Port : public Node {
private:
    PortDirection direction;
public:
    Port(PortDirection direction, Component* topLevel, Model* parent);
};

// TODO documentation
// TODO visitors
class ConductorNode : public Node {
public:
    ConductorNode();
};

} // namespace model
} // namespace q2d

#endif // NODE_H
