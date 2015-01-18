#include "ComponentDescriptor.h"

#include "ComponentCategory.h"
#include "Constants.h"

using namespace q2d::metamodel;
using namespace q2d::constants;

/**
 * @brief ComponentDescriptor::ComponentDescriptor
 * This also generates the hierarchy name.
 * A hierarchy name is the name of the descriptor including all parent categories.
 * The resulting string looks like a file path, but without the leading slash ("/").
 *
 * Since the hierarchy name is cached be careful to update it when manipulating the hierarchy.
 *
 * @param name
 * @param parent
 */
ComponentDescriptor::ComponentDescriptor(QString name, ComponentCategory* parent) :
    QObject(parent),
    QStandardItem(name){

    QString hierarchyName;
    if(parent == nullptr){
        hierarchyName =  this->text();
    } else {
        hierarchyName = parent->hierarchyName() + HIERARCHY_SEPERATOR + this->text();
    }

    this->setData(hierarchyName, ComponentDescriptorRole::HIERARCHY_NAME);
}

/**
 * @brief ComponentDescriptor::hierarchyName is a convenience getter.
 *
 * @return
 */
QString
ComponentDescriptor::hierarchyName(){

    return this->data(ComponentDescriptorRole::HIERARCHY_NAME).toString();
}
