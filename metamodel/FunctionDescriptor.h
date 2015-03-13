#ifndef FUNCTIONDESCRIPTOR_H
#define FUNCTIONDESCRIPTOR_H

#include "ComponentElement.h"

namespace q2d {
namespace metamodel {

class FunctionDescriptor
        : public ComponentElement {
private:
public:
    explicit FunctionDescriptor(QString function, ComponentDescriptor* parent);

    virtual int type() const override {
        return enums::elementTypeToInt(enums::ElementType::FUNCTION);
    }
};

} // namespace metamodel
} // namespace q2d

#endif // FUNCTIONDESCRIPTOR_H
