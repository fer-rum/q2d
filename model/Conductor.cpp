#include "../DocumentEntry.h"
#include "Conductor.h"

using namespace q2d::model;

/**
 * @brief Conductor::Conductor
 * Conductors are assigned a default name for convenience. It can be changed later.
 *
 * @param start
 * @param end
 */
Conductor::Conductor(Node* start, Node* end, Model* model, DocumentEntry* relatedEntry)
    : ModelElement(model, relatedEntry) {
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    this->m_start = start;
    this->m_end = end;
}

QStringList
Conductor::nodeVariables() const {
    Q_CHECK_PTR(m_start->relatedEntry());
    Q_CHECK_PTR(m_end->relatedEntry());

    QStringList result;
    result.append(m_start->relatedEntry()->id());
    result.append(m_end->relatedEntry()->id());

    return result;
}

QStringList
Conductor::functions() const {

    Q_CHECK_PTR(m_start->relatedEntry());
    Q_CHECK_PTR(m_end->relatedEntry());

    QString function(m_start->relatedEntry()->id() + " = " + m_end->relatedEntry()->id());

    return QStringList(function);
}

