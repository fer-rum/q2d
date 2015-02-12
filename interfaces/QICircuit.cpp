#include "QICircuit.h"
#include "Quantor.h"


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
            default:
            // TODO warning
            }
        }
    }
}

Iterator<unsigned int>
QICircuit::configVars() {
    QList::iterator begin = m_inputVars.begin();
    QList::iterator end = m_inputVars.end();
    return Iterator<unsigned int>(begin, end);
}

Iterator<unsigned int>
QICircuit::inputVars() {
    QList::iterator begin = m_inputVars.begin();
    QList::iterator end = m_inputVars.end();
    return Iterator<unsigned int>(begin, end);
}

Iterator<unsigned int>
QICircuit::nodeVars() {
    QList::iterator begin = m_nodeVars.begin();
    QList::iterator end = m_nodeVars.end();
    return Iterator<unsigned int>(begin, end);
}

Iterator<QIContext>
QICircuit::contexts(){
    QList::iterator begin = m_interface->contexts().values().begin();
    QList::iterator end = m_interface->contexts().values().end();
    return Iterator<QIContext>(begin, end);
}
