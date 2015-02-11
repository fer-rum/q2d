#include "QIContext.h"
#include "Iterator.h"

#include "../../model/ModelElement.h"
#include "../../Util.h"

#include "QtDebug"

using namespace q2d::quantor;

QIContext::QIContext(QString contextName, unsigned int lowestIndex,
                     model::ModelElement* contextSource ) {
    m_contextName = contextName;
    m_lowestIndex = lowestIndex;
    m_highestIndex = m_lowestIndex;


    for (QString varName : contextSource->nodeVariables()) {
        this->assignVariable(varName, VariableType::NODE);
    }

    for (QString varName : contextSource->configVariables()) {
        this->assignVariable(varName, VariableType::NODE);
    }

    for (QString function : contextSource->functions()) {
        m_functions.append(function.toStdString());
    }
}

void
QIContext::assignVariable(QString varName, VariableType type) {
    const QString logPrefix = "assignVariable(" + varName + ", " + (int)type + ")";

    if (m_variableMapping.contains(varName)) {
        qWarning() << logPrefix << "Duplicate variable name " << varName << "ignored";
    } else {
        qDebug() << logPrefix << "Variable assignment:"
                 << varName << "->" << util::intToString(m_highestIndex);
        m_variableMapping.insert(varName, m_highestIndex);
        m_typeMapping.insert(m_highestIndex, type);
        m_highestIndex ++;

    }
}

QStringList
QIContext::varNames() const {
    return m_variableMapping.keys();
}

/**
 * @brief QIContext::operator []
 * @param varName
 * @return the number corresponding to the variable or 0 if the name is invalid.
 */
unsigned int
QIContext::operator[](std::string const &varName) const {
    QString name = QString::fromStdString(varName);
    if (m_variableMapping.contains(name)) {
        return m_variableMapping[name];
    } else {
        return 0;
    }
}

/**
 * @brief QIContext::typeOf requests the type of a given variable within this context.
 * @param variable
 * @return the type of the variable or VariableType::INVALID on error.
 */
VariableType
QIContext::typeOf(unsigned int variable) const {
    if (m_typeMapping.contains(variable)) {
        return m_typeMapping[variable];
    }
    return VariableType::INVALID;
}

VariableType
QIContext::typeOf(std::string varName) const {
    unsigned int var = (*this)[varName];
    if (var == 0) {
        return VariableType::INVALID;
    } else {
        return this->typeOf(var);
    }
}

Iterator<QList<std::string>::const_iterator>
QIContext::functionIterator() const {
  return  Iterator<QList<std::string>::const_iterator>(m_functions.begin(), m_functions.end());
}
