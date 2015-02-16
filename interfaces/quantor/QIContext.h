#ifndef Q2D_QUANTOR_QICONTEXT_H
#define Q2D_QUANTOR_QICONTEXT_H

#include "Iterator.h"
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
    QString m_contextName;
    /**
     * @brief m_lowestIndex is the lowest variable index that is in use by this context.
     */
    unsigned int m_lowestIndex;

    /**
     * @brief m_highestIndex is the highest variable index that is in use by this context.
     * If the m_highestIndex is smaller then the m_lowestIndex, there is no variable assigned at all.
     * If the m_highestIndex equals the m_lowestIndex, ther is exactly one variable assigned.
     */
    unsigned int m_highestIndex;

    QMap<QString, unsigned int> m_variableMapping;
    QMap<unsigned int, VariableType> m_typeMapping;
    QList<std::string> m_functions;

    void assignVariable(QString varName, VariableType type);

public:
    QIContext(QString contextName, unsigned int lowestIndex, model::ModelElement* contextSource);

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
     * @brief functionIterator
     * @return an iterator over all available function strings in the context
     */
    Iterator<QList<std::string>::const_iterator> functionIterator() const; // TBP-compat
};

} // namespace quantor
} // namespace q2d


#endif // QICONTEXT_H
