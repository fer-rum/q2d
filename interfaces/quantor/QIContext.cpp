#include "QIContext.h"

#include "../../Constants.h"
#include "../../model/ModelElement.h"
#include "../../Util.h"

// for debug purposes
#include "../../DocumentEntry.h"
#include <QMap>
#include "QtDebug"

using namespace q2d::constants;
using namespace q2d::quantor;

QIContext::QIContext(unsigned int lowestIndex,
                     model::ModelElement* const contextSource , QIContext* parent)
    : QIContext(lowestIndex, parent) {
    qDebug() << "Creating context for" << contextSource->relatedEntry()->fullId();
    this->addModelElement(*contextSource);
}

QIContext::QIContext(unsigned int lowestIndex, QIContext* parent) {
    m_parent = parent;
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
    for (QString varName : element.inputVariables()) {
        this->assignVariable(varName, VariableType::INPUT);
    }

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
    qDebug() << "Added function" << function;
}

void
QIContext::assignVariable(QString varName, VariableType type) {
    const QString logPrefix = "assignVariable(" + varName + ", " + util::intToString((int)type) + ")";
    QString varNameShort = varName.split(HIERARCHY_SEPERATOR).last();

    // check if this variable is already known in a parent context
    if (m_parent != nullptr) {
        unsigned int index = (*m_parent)[varName.toStdString()];
        if (index != 0) {
            qDebug() << "Variable already known in parent context as" << util::intToString(index);
            m_variableMapping.insert(varNameShort, index);
            m_typeMapping.insert(index, type);
            return;
        }
    }

    if (m_variableMapping.contains(varName)) {
        qWarning() << logPrefix << "Duplicate variable name " << varName << "ignored";
    } else {
        m_highestIndex ++;
        if (m_parent == nullptr) {
            m_variableMapping.insert(varName, m_highestIndex);
            qDebug() << logPrefix << "Variable assignment:"
                     << varName << "->" << util::intToString(m_highestIndex);
        } else {
            m_variableMapping.insert(varNameShort, m_highestIndex);
            qDebug() << logPrefix << "Variable assignment:"
                     << varNameShort << "->" << util::intToString(m_highestIndex);
        }
        m_typeMapping.insert(m_highestIndex, type);
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
        unsigned int result = m_variableMapping[name];
        qDebug() << "QIContext::operator[" << varName.c_str() << "] returned" << result;
        return result;
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

void
QIContext::dumpMaps() {
    qDebug() << "=== Dumping Context ===";
    qDebug() << "variable assignments:";
    QMapIterator<QString, unsigned> iterVar(m_variableMapping);
    while (iterVar.hasNext()) {
        iterVar.next();
        qDebug() << iterVar.key() << "->" << QString::number(iterVar.value());
    }

    qDebug() << "variable types:";
    QMapIterator<unsigned, VariableType> iterType(m_typeMapping);
    while (iterType.hasNext()) {
        iterType.next();
        qDebug() << QString::number(iterType.key()) << "->" << QString::number((int)iterType.value());
    }

    qDebug() << "Functions:";
    for (std::string entry : m_functions) {
        qDebug() << QString::fromStdString(entry);
    }

    qDebug() << "=== End dump ===";
}
