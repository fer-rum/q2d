#include "QICircuit.h"
#include "../Quantor.h"


using namespace q2d::quantor;

QICircuit::QICircuit(QuantorInterface const &interface) : m_interface(interface) {
    for(QIContext const &context : interface.contexts()) {
        for (QString const &varName : context.varNames()) {
            unsigned int const  var = context[varName.toStdString()];
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
