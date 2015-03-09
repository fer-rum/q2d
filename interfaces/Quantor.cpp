
#include "../Document.h"
#include "../DocumentEntry.h"
#include "../model/Component.h"
#include "../model/Conductor.h"
#include "../model/Model.h"
#include "../model/ModelElement.h"
#include "../model/Port.h"
#include "../Util.h"

#include "quantor/ParseException.h"
#include "quantor/QICircuit.h"
#include "quantor/Quantorizer.hpp"
#include "quantor/Result.h"
#include "Quantor.h"

#include <QtDebug>

using namespace q2d::quantor;

QuantorInterface::QuantorInterface() {}

void
QuantorInterface::buildContexts(q2d::model::Model const &contextSource,
                                QString const targetFunction) {

    const QString GLOBAL_CONTEXT_NAME = "global";

    unsigned int currentIndex = 1;
    // build contexts from components

    // create the global context
    qDebug() << "Building global context";
    QIContext globalContext = QIContext(currentIndex);
    globalContext.addFunction(targetFunction);

    // IMPORTANT: build the ports before the wires
    // otherwise the generated context is wrong
    for (model::ModulePort * port : contextSource.outsidePorts()) {
            globalContext.addModelElement(*port);
    }

    for (model::ModelElement * wire : contextSource.conductors()) {
        globalContext.addModelElement(*wire);
    }

    currentIndex = globalContext.highestIndex() + 1;
    m_contexts.insert(GLOBAL_CONTEXT_NAME, globalContext);
    globalContext.dumpMaps();

    qDebug() << "Building component contexts";
    for (model::ModelElement * c : contextSource.components()) {
        QIContext newContext = QIContext(currentIndex, c, &globalContext);
        currentIndex = newContext.highestIndex() + 1;
        m_contexts.insert(c->relatedEntry()->id(), newContext);
        newContext.dumpMaps();
    }
}

void
QuantorInterface::slot_solveProblem(Document* targetDocument, QString targetFunction) {

    qDebug() << "SLOT QuantorInterface::solveProblem called.";

    // get the model
    const model::Model* contextSource = targetDocument->model();
    this->buildContexts(*contextSource, targetFunction);

    // call the solver

    Quantorizer  q;
    {
        // Build the Problem
        QICircuit circuit = QICircuit(*this);
        for (QIContext const & ctx : circuit.contexts()) {
            q.set(ctx);
            for (std::string const & fct : ctx.functions()) {
                try {
                    q.parse(fct.c_str());
                } catch (ParseException const &exc) {
                    qWarning() << "ParseException in context" << m_contexts.key(ctx) << ".\"" << fct.c_str() << "\"@" << QString::number(exc.position()) << ":" ;
                    qWarning() << exc.message().c_str();
                    return;
                }
            }
        }
    }
    std::vector<int> rawSolution;
    Result const  result = q.solve(rawSolution);
    QVector<int> qVector = QVector<int>::fromStdVector(rawSolution);
    m_solution = QList<int>::fromVector(qVector);

    // --- --- ---

    Q_ASSERT(!(qVector.isEmpty() && !rawSolution.empty()));
    Q_ASSERT(!(m_solution.isEmpty() && !rawSolution.empty()));

    // DEBUG
    qDebug() << "Solutions:";
    for (int i : m_solution) {
        qDebug() << util::intToString(i);
    }
    // END DEBUG

    this->interpreteSolution(result);

}

void
QuantorInterface::interpreteSolution(const Result &result) {

    QString textualResult = QString(result);
    qDebug() << textualResult;

    if (result.isSatisfiable()) {
        // resolve variable numbers to names and
        // translate sign to truth value

        // TODO it is sufficient to onle ask for configVars. Others will not be included in the solution
        QMap<QString, bool>* resultMapping = new QMap<QString, bool>();

        QMapIterator<QString, QIContext> contextIter(m_contexts);
        while (contextIter.hasNext()) {
            contextIter.next();
            QIContext actualContext = contextIter.value();
            for (QString varName : actualContext.varNames()) {
                int index = actualContext[varName.toStdString()];
                if (m_solution.contains(index)) {
                    resultMapping->insert(contextIter.key() + "/" + varName, true);
                } else if (m_solution.contains(-index)) {
                    resultMapping->insert(contextIter.key() + "/" + varName, false);
                } else {
                    qDebug() << "Solution did not contain variable"
                             << varName << "with index" << util::intToString(index);
                }
            }
        }
        qDebug() << "Sending result and solution";
        emit signal_hasSolution(textualResult, resultMapping);
    } else {
        qDebug() << "Sending result";
        emit signal_hasSolution(textualResult, nullptr);
    }
}
