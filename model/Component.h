#ifndef COMPONENT_H
#define COMPONENT_H

#include "Model.h"
#include "ModelElement.h"
#include "Node.h"

#include <QList>

namespace q2d {
namespace model {

    // ahead declaration
    class Model;

// TODO documentation
// TODO visitor-pattern
// TODO a component should observe its internal model to be informed of changes
class Component : public ModelElement {
private:
    QList<Port*> ports;
    Model* internalModel;
public:
    Component(QString name, Model* internalModel = nullptr);
};

} // namespace model
} // namespace q2d

#endif // COMPONENT_H
