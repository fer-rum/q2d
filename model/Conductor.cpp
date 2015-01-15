#include "Conductor.h"

using namespace q2d::model;

int Conductor::DEFAULT_NAME_INDEX = 0;

/**
 * @brief Conductor::Conductor
 * Conductors are assigned a default name for convenience. It can be changed later.
 *
 * @param start
 * @param end
 */
Conductor::Conductor(Node *start, Node *end) : ModelElement(tr("conductor " + DEFAULT_NAME_INDEX)) {
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    this->start = start;
    this->end = end;
    ++DEFAULT_NAME_INDEX;
}
