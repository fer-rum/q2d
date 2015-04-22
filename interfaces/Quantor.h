#ifndef INTERFACE_H
#define INTERFACE_H

#include "quantor/QIContext.h"

#include <vector>
#include <string>

#include <QMap>
#include <QList>
#include <QObject>

namespace q2d {

// forward declaration
class Document;

namespace model {
class Model;
}

namespace quantor {
class QICircuit;
class Result;

/**
 * @brief The Quantor class provides utility functions and keeps the state necessary for interfacing with the tool quantor.
 */
class QuantorInterface :
    public QObject {
    Q_OBJECT
private:

    // NOTE make sure, the lowest variable index is 1, NOT 0
    // since 0 is already used by quantor for terminating

    QMap<QString, QIContext> m_contexts;

    QList<int> m_solution;

    // helper functions
    void buildContexts(const q2d::model::Model &contextSource, const QString targetFunction);
    QList<unsigned int> varsForType(VariableType requestedType, QList<unsigned int>* container);
    void interpreteSolution(const Result &result);
public:
    QuantorInterface();
    QMap<QString, QIContext> const &contexts() const {
        return m_contexts;
    }

public slots:
    void slot_solveProblem(q2d::Document* targetDocument, QString targetFunction);

signals:
    /**
     * @brief signal_hasSolution is supposed to be raised when a solution from Quantor is available.
     * @param textualRepresentation summarizes the result in textual form.
     * @param variableMapping provides a mapping from variable names to truth values if there was found one.
     * This may be null, if the result does not incorporate a variable assignment
     */
    void signal_hasSolution(QString textualRepresentation, const QMap<QString, bool>* variableMapping);
    // TODO better wrap the parameters in a solution object.
};

} // namespace quantor
} // namespace q2d


#endif // INTERFACE_H
