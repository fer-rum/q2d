#ifndef NODE_H
#define NODE_H

#include "ModelElement.h"
#include "PortDirection.h"

#include <QList>

namespace q2d {
namespace model {

// TODO documentation
// TODO visitor pattern
// TODO implementation
class Node : public ModelElement {
private:
    static int DEFAULT_NAME_INDEX;

    QList<ModelElement*> drivenElements;
    ModelElement* driver;
public:
    Node();
    Node(QString name);

    void addDriver(ModelElement* driver);
    void addDrivenElement(ModelElement* drivenElement);
};

// TODO visitor-pattern
// TODO documentation
class Port : public Node {
private:
    PortDirection direction;
public:
    Port(QString name, PortDirection direction = UNSPECIFIED);
};

// TODO documentation
// TODO visitors
class ConductorNode : public Node {
public:
    ConductorNode(QString name = "");
};

} // namespace model
} // namespace q2d

#endif // NODE_H
