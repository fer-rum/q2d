#include "Component.h"

using namespace q2d::model;

Component::Component(QString name, Model* internalModel) : ModelElement(name) {
    this->internalModel = internalModel;
}
