#include "Circuit.hpp"
#include "../Quantor.h"


using namespace q2d::quantor;

QICircuit::QICircuit(QuantorInterface* interface)
    : m_interface(interface){
Q_CHECK_PTR(interface);

    for (QIContext context : interface->contexts().values()) {
        for (QString varName : context.varNames()) {
            unsigned int var = context[varName.toStdString()];
            switch(context.typeOf(var)){
            case VariableType::CONFIG :
                m_configVars.append(var);
                break;
            case VariableType::INPUT :
                m_inputVars.append(var);
                break;
            case VariableType::NODE :
                m_nodeVars.append(var);
                break;
            default:;
            // TODO warning
            }
        }
    }
}
