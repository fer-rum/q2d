

#include "../model/Model.h"
#include "../model/Component.h"
#include "Quantor.h"
#include "QIContext.h"

using namespace q2d::quantor;


Iterator<unsigned int> QuantorInterface::configVars() {
    return this->varsForType(VariableType::CONFIG, &m_configVars);
}

Iterator<unsigned int> QuantorInterface::inputVars() {
    return this->varsForType(VariableType::INPUT, &m_inputVars);
}

Iterator<unsigned int> QuantorInterface::nodeVars() {
    return this->varsForType(VariableType::NODE, &m_nodeVars);
}


Iterator<unsigned int>
QuantorInterface::varsForType(VariableType requestedType, QList<unsigned int> *container) {

    for (QIContext context : m_contexts.values()) {
        for (QString varName : context.varNames()) {
            unsigned int var = context[varName.toStdString()];
            if (context.typeOf(var) == requestedType) {
                container->append(var);
            }
        }
    }

}

void
QuantorInterface::buildContexts(const q2d::model::Model* contextSource) {
    // build contexts from components
    // remember full component IDs to recognize them in wire contexts
    // build global contexts from wires
    // build global contexts from schematic ports



}

void
QuantorInterface::slot_solveProblem() {
    // TODO implement
}
