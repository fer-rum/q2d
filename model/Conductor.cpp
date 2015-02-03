#include "Conductor.h"

using namespace q2d::model;

/**
 * @brief Conductor::Conductor
 * Conductors are assigned a default name for convenience. It can be changed later.
 *
 * @param start
 * @param end
 */
Conductor::Conductor(Node* start, Node* end, Model* model) : ModelElement(model) {
    Q_CHECK_PTR(start);
    Q_CHECK_PTR(end);

    this->start = start;
    this->end = end;
}
