#include "FunctionDescriptor.h"

using namespace q2d::metamodel;

FunctionDescriptor::FunctionDescriptor(QString function, ComponentDescriptor* parent)
    : ComponentElement(function, parent){
    this->setIcon(QIcon(":/icons/ressources/icons/function.svg"));
    this->setToolTip(function);
}
