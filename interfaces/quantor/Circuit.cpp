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

Iterator<QList<unsigned int>::const_iterator>
QICircuit::configVars() {
    QList<unsigned int>::iterator begin = m_inputVars.begin();
    QList<unsigned int>::iterator end = m_inputVars.end();
    return Iterator<QList<unsigned int>::const_iterator>(begin, end);
}

Iterator<QList<unsigned int>::const_iterator>
QICircuit::inputVars() {
    QList<unsigned int>::iterator begin = m_inputVars.begin();
    QList<unsigned int>::iterator end = m_inputVars.end();
    return Iterator<QList<unsigned int>::const_iterator>(begin, end);
}

Iterator<QList<unsigned int>::const_iterator>
QICircuit::nodeVars() {
    QList<unsigned int>::iterator begin = m_nodeVars.begin();
    QList<unsigned int>::iterator end = m_nodeVars.end();
    return Iterator<QList<unsigned int>::const_iterator>(begin, end);
}

Iterator<QList<QIContext>::const_iterator>
QICircuit::contexts(){
    QList<QIContext>::iterator begin = m_interface->contexts().values().begin();
    QList<QIContext>::iterator end = m_interface->contexts().values().end();
    return Iterator<QList<QIContext>::const_iterator>(begin, end);
}
