#ifndef INTERFACE_H
#define INTERFACE_H

#include "Iterator.h"
#include "QIContext.h"

#include <string>

#include <QMap>
#include <QList>
#include <QObject>

namespace q2d {

// forward declaration
namespace model {
class Component;
class Model;
class Node;
}

namespace quantor {

/**
 * @brief The Quantor class provides utility functions and keeps the state necessary for interfacing with the tool quantor.
 */
class QuantorInterface :
        QObject {
    Q_OBJECT
private:

    // NOTE make sure, the lowest variable index is 1, NOT 0
    // since 0 is already used for terminating

    QMap<QString, QIContext> m_contexts;
    QList<unsigned int> m_configVars;
    QList<unsigned int> m_inputVars;
    QList<unsigned int> m_nodeVars;

    // the solver will return a zero-terminated array of int
    int* (*m_solverMain)(void) = nullptr;
    QList<QList<int>> m_solutions;

    // helper functions
    void buildContexts(const q2d::model::Model* contextSource);
    Iterator<unsigned int> varsForType(VariableType requestedType, QList<unsigned int>* container);

    // creates the thread and collects the result once it finfished
    void solve();
public:
    QuantorInterface(int * (*solverMain)(void));

    // functions for the quantor wrapper for requesting needed information
    Iterator<QIContext> contexts();
    QIContext* context(std::string context);

    /**
     * @brief configVars fetches all configuration variables in all contexts.
     * Excludes input variables
     * @return
     */
    Iterator<unsigned int> configVars();

    /**
     * @brief nodeVars fetches all node variables in all contexts.
     * Excludes input variables, but includes output vars, since they need no extra handling.
     * @return
     */
    Iterator<unsigned int> nodeVars();

    /**
     * @brief inputVars fetches all schematic-wide I/O-port variables
     * @return
     */
    Iterator<unsigned int> inputVars();

public slots:
    void slot_solveProblem();
};



} // namespace quantor
} // namespace q2d


#endif // INTERFACE_H
