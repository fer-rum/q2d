#ifndef Q2D_QUANTOR_QICONTEXT_H
#define Q2D_QUANTOR_QICONTEXT_H

#include "VariableType.h"

#include <QString>
#include <QStringList>
#include <QMap>

namespace q2d {

namespace model {
class ModelElement;
}

namespace quantor {

/**
 * @brief The QIContext class wraps the access to the context-based information of the QuantorInterface.
 */
class QIContext {

private:

    QIContext* m_parent;

    /**
     * @brief m_lowestIndex is the lowest variable index that is in use by this context.
     */
    unsigned int m_lowestIndex;

    /**
     * @brief m_highestIndex is the highest variable index that is in use by this context.
     * If the m_highestIndex is smaller then the m_lowestIndex, there is no variable assigned at all.
     * If the m_highestIndex equals the m_lowestIndex, there is exactly one variable assigned.
     */
    unsigned int m_highestIndex;

    QMap<QString, unsigned int> m_variableMapping;
    QMap<unsigned int, VariableType> m_typeMapping;
    QList<std::string> m_functions;

    void assignVariable(QString varName, VariableType type);

public:

    /**
     * @brief QIContext creates a minimal, empty context to be filled manually.
     * @param contextName
     * @param lowestIndex
     */
    QIContext(unsigned int lowestIndex, QIContext* parent = nullptr);
    QIContext(unsigned int lowestIndex, model::ModelElement* const contextSource,
              QIContext* parent = nullptr);

    bool operator==(QIContext const &other) const;

    void addModelElement(model::ModelElement const &element);
    void addFunction(QString function);


    QStringList varNames() const;
    unsigned int lowestIndex() const    {
        return m_lowestIndex;
    }
    unsigned int highestIndex() const   {
        return m_highestIndex;
    }

    /** Fetches the global variable number for a given variable name in the context.
     */
    unsigned int operator[](std::string const &varName) const; // TBP-compat
    VariableType typeOf(unsigned int variable) const;
    VariableType typeOf(std::string varName) const;

    /**
     * @brief functions
     * @return  all available function strings in the context
     */
    QList<std::string> const &functions() const {
        return  m_functions;
    }

    /**
     * @brief dumpMaps is a helper function for debugging
     */
    void dumpMaps();
};

} // namespace quantor
} // namespace q2d


#endif // QICONTEXT_H
