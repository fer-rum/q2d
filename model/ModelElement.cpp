#include "ModelElement.h"

#include "Model.h"

using namespace q2d::model;

ModelElement::ModelElement(QString name, Model* parent)
    : QObject(parent){
    this->name = name;
}
