

#include "../DocumentEntry.h"
#include "../model/Model.h"
#include "../model/Component.h"


#include "Quantor.h"

using namespace q2d::quantor;

void
QuantorInterface::buildContexts(const q2d::model::Model* contextSource) {

    unsigned int currentIndex = 1;
    // build contexts from components

    for(model::Component* c : contextSource->components()){
        QIContext newContext = QIContext(c->relatedEntry()->id(), currentIndex, c);
        currentIndex = newContext.highestIndex() + 1;
    }

    // remember full component IDs to recognize them in wire contexts
    // build global contexts from wires
    // build global contexts from schematic ports
}

void
QuantorInterface::slot_solveProblem() {
    // TODO get the model
    this->buildContexts(contextSource);
    // call the solver
    // interprete the result
}
