#ifndef CONFIGURATIONBIT_H
#define CONFIGURATIONBIT_H

#include "../Enumerations.h"

#include "ModelElement.h"

namespace q2d {
namespace model {

// forward declaration
class Model;
class ModelElement;

class ConfigurationBit : public ModelElement {
private:
    model::enums::ConfigurationBitState m_state;
public:
    ConfigurationBit(q2d::model::Model* parent);

    model::enums::ConfigurationBitState state() const;
    void setState(model::enums::ConfigurationBitState state);
    void clearState();
};

} // namespace model
} // namespace q2d

#endif // CONFIGURATIONBIT_H
