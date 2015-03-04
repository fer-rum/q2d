#include "QIContext.h"

#include "../../model/ModelElement.h"
#include "../../Util.h"

// for debug purposes
#include "../../DocumentEntry.h"

#include "QtDebug"

using namespace q2d::quantor;

QIContext::QIContext(unsigned int lowestIndex,
                     model::ModelElement* const contextSource )
    : QIContext(lowestIndex) {
    this->addModelElement(*contextSource);
    qDebug() << "Context Creation: creating context for" << contextSource->relatedEntry()->id();
}

QIContext::QIContext(unsigned int lowestIndex) {
    m_lowestIndex = lowestIndex;
    m_highestIndex = m_lowestIndex - 1;
    qDebug() << "Context Creation: lowest index is" << util::intToString(m_lowestIndex);
}

bool
QIContext::operator==(QIContext const &other) const {
    if (this == &other) {
        return true;
    }

    if (m_lowestIndex != other.m_lowestIndex
            || m_highestIndex != other.m_highestIndex) {
        return false;
    }

    if (m_variableMapping == other.m_variableMapping
            && m_typeMapping == other.m_typeMapping) {
        return true;
    }
    return false;
}

void
QIContext::addModelElement(model::ModelElement const &element) {
    for (QString varName : element.nodeVariables()) {
        this->assignVariable(varName, VariableType::NODE);
    }

    for (QString varName : element.configVariables()) {
        this->assignVariable(varName, VariableType::CONFIG);
    }

    for (QString function : element.functions()) {
        m_functions.append(function.toStdString());
    }
}

void
QIContext::addFunction(QString function) {
    m_functions.append(function.toStdString());
}

void
QIContext::assignVariable(QString varName, VariableType type) {
    const QString logPrefix = "assignVariable(" + varName + ", " + util::intToString((int)type) + ")";

    if (m_variableMapping.contains(varName)) {
        qWarning() << logPrefix << "Duplicate variable name " << varName << "ignored";
    } else {
        m_highestIndex ++;
        m_variableMapping.insert(varName, m_highestIndex);
        m_typeMapping.insert(m_highestIndex, type);
        qDebug() << logPrefix << "Variable assignment:"
                 << varName << "->" << util::intToString(m_highestIndex);
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
        qDebug() << "QIContext::operator[" << varName.c_str() << "] failed";
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
