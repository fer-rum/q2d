#include "Conductor.h"

using namespace q2d::model;

/**
 * @brief Conductor::Conductor
 * Conductors are assigned a default name for convenience. It can be changed later.
 *
 * @param start
 * @param end
 */
Conductor::Conductor(Node* start, Node* end, Model* model,
                     DocumentEntry* relatedEntry) : ModelElement(model, relatedEntry) {
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    this->m_start = start;
    this->m_end = end;
}
