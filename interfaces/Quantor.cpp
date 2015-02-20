
#include "../Document.h"
#include "../DocumentEntry.h"
#include "../model/Component.h"
#include "../model/Conductor.h"
#include "../model/Model.h"
#include "../model/ModelElement.h"

#include "quantor/ParseException.h"
#include "quantor/QICircuit.h"
#include "quantor/Quantorizer.hpp"
#include "quantor/Result.h"
#include "Quantor.h"

#include <QtDebug>

using namespace q2d::quantor;

QuantorInterface::QuantorInterface(){
    m_solverMain = &Quantorizer::solve;
}

void
QuantorInterface::buildContexts(q2d::model::Model const &contextSource, QString const targetFunction) {

    const QString GLOBAL_CONTEXT_NAME = "global";

    unsigned int currentIndex = 1;
    // build contexts from components

    // create the global context
    // TODO remember full component IDs to recognize them in wire contexts
    // the global context includes wires and ports to the outside world
    qDebug() << "Building global context";
    QIContext globalContext = QIContext(currentIndex);
    globalContext.addFunction(targetFunction);

    for(model::ModelElement* wire : contextSource.conductors()){
        globalContext.addModelElement(*wire);
    }

    for(model::ModelElement* port : contextSource.outsidePorts()){
        globalContext.addModelElement(*port);
    }
    currentIndex = globalContext.highestIndex() + 1;
    m_contexts.insert(GLOBAL_CONTEXT_NAME, globalContext);

    qDebug() << "Building component contexts";
    for(model::ModelElement* c : contextSource.components()){
        QIContext newContext = QIContext(currentIndex, c);
        currentIndex = newContext.highestIndex() + 1;
        m_contexts.insert(c->relatedEntry()->id(), newContext);
    }
}

void
QuantorInterface::slot_solveProblem(Document* targetDocument, QString targetFunction) {

    qDebug() << "SLOT QuantorInterface::solveProblem called.";

    // get the model
    const model::Model* contextSource = targetDocument->model();
    this->buildContexts(*contextSource, targetFunction);

    // call the solver
    std::vector<int> rawSolution;
    Q_CHECK_PTR(m_solverMain);

    try {
        Result result = this->m_solverMain(QICircuit(*this), rawSolution);
        qDebug() << QString(result);
    } catch (ParseException const &exception){
        const QIContext& failedCtx = exception.context();
        qWarning() << "In context" << m_contexts.key(failedCtx);
        qWarning() << QString::fromStdString(exception.message());
        return;
    }
    // interprete the result
    m_solution.fromVector(QVector<int>::fromStdVector(rawSolution));
    // TODO continue give feedback
}
