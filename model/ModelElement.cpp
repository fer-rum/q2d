#include "ModelElement.h"

#include "Model.h"

using namespace q2d::model;

ModelElement::ModelElement(Model* parent)
    : QObject(parent){}

Model*
ModelElement::model() const {
    return qobject_cast<Model*>(this->parent());
}
