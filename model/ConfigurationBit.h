#ifndef CONFIGURATIONBIT_H
#define CONFIGURATIONBIT_H

#include "../Enumerations.h"

#include "ModelElement.h"

namespace q2d {
namespace model {

// forward declaration
class Model;
class ModelElement;

class ConfigurationBit : public ModelElement
{
private:
    ConfigurationBitState m_state;
public:
    ConfigurationBit(q2d::model::Model* parent);

    ConfigurationBitState state() const;
    void setState(ConfigurationBitState state);
    void clearState();
};

} // namespace model
} // namespace q2d

#endif // CONFIGURATIONBIT_H
