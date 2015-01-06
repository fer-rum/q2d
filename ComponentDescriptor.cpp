#include "ComponentDescriptor.h"

#include "ComponentCategory.h"

using namespace q2d;

ComponentDescriptor::ComponentDescriptor(QString name, ComponentCategory* parent) :
    QObject(parent),
    QStandardItem(name){}


