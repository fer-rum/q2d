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
class Port : public Node {
private:
    enums::PortDirection m_direction;
public:
    /**
     * @brief Port
     * @param direction
     * @param topLevel may be nullptr in case this is an outside port
     * @param parent
     * @param relatedEntry
     */
    Port(enums::PortDirection direction, Component* topLevel, Model* parent,
         DocumentEntry* relatedEntry = nullptr);

    enums::PortDirection direction() const {
        return m_direction;
    }

    virtual QStringList nodeVariables() const override;
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
