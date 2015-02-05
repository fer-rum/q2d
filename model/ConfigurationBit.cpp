#include "ConfigurationBit.h"

#include "Model.h"

using namespace q2d::model;

ConfigurationBit::ConfigurationBit(Model* parent) :  ModelElement(parent){
    m_state = enums::ConfigurationBitState::NOT_SET;
}

enums::ConfigurationBitState
ConfigurationBit::state() const {
    return m_state;
}

void
ConfigurationBit::setState(enums::ConfigurationBitState state){
    m_state = state;
}

void
ConfigurationBit::clearState(){
    m_state = enums::ConfigurationBitState::NOT_SET;
}
