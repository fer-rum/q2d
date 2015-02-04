#include "ConfigurationBit.h"

#include "Model.h"

using namespace q2d::model;

ConfigurationBit::ConfigurationBit(Model* parent) :  ModelElement(parent){
    m_state = ConfigurationBitState::NOT_SET;
}

q2d::ConfigurationBitState
ConfigurationBit::state() const {
    return m_state;
}

void
ConfigurationBit::setState(ConfigurationBitState state){
    m_state = state;
}

void
ConfigurationBit::clearState(){
    m_state = ConfigurationBitState::NOT_SET;
}
