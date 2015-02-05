#include "HierarchyElement.h"

#include "Category.h"
#include "../Constants.h"

#include <QtDebug>

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
HierarchyElement::HierarchyElement(QString name, Category* parent) :
    Element(name, parent) {

    QString hierarchyName;
    if (parent == nullptr) {
        hierarchyName =  this->text();
    } else {
        hierarchyName = parent->hierarchyName() + HIERARCHY_SEPERATOR + this->text();
    }

    qDebug() << "Hierarchy name =" << hierarchyName;

    this->setData(hierarchyName, ComponentDescriptorRole::HIERARCHY_NAME);
}

HierarchyElement*
HierarchyElement::parent() const {
    return static_cast<HierarchyElement*>(QObject::parent());
}

void
HierarchyElement::setParent(HierarchyElement* parent){
    QObject::setParent(parent);
}

/**
 * @brief ComponentDescriptor::hierarchyName is a convenience getter.
 *
 * @return
 */
QString
HierarchyElement::hierarchyName() {

    return this->data(ComponentDescriptorRole::HIERARCHY_NAME).toString();
}
