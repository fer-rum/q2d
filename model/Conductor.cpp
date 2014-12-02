#include "Conductor.h"

using namespace q2d::model;

Conductor::Conductor(Node *start, Node *end, QString name) : ModelElement(name) {
    this->start = start;
    this->end = end;
}
