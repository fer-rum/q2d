#ifndef NODE_H
#define NODE_H

#include "../Enumerations.h"
#include "ModelElement.h"

#include <QList>
#include <QStringList>

namespace q2d {
namespace model {

// forward declaration
class Component;

// TODO documentation
class Node : public ModelElement {
private:
    QList<ModelElement*> drivenElements;
    ModelElement* driver;
public:
    Node(Model* parent, DocumentEntry* relatedEntry);

    // TODO rename to better reflect actual function
    void addDriver(ModelElement* driver);
    void addDrivenElement(ModelElement* drivenElement);
};

// TODO documentation
// NOTE currently unused
class ConductorNode : public Node {
public:
    ConductorNode();
};

} // namespace model
} // namespace q2d

#endif // NODE_H
