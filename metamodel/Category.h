#ifndef COMPONENTCATEGORY_H
#define COMPONENTCATEGORY_H

#include"../Enumerations.h"
#include "HierarchyElement.h"

namespace q2d {
namespace metamodel {

/**
 * @brief The Category class is a pure container for other q2d::metamodel::HierarchyElement-objects.
 */
class Category :
        public HierarchyElement {
    // TODO later: mouse-over descriptions
    // TODO later: translations for names?
public:
    explicit Category(QString name, Category* parent = nullptr);

    void addSubItem(HierarchyElement* toAdd);

    virtual int type() const override;
};

} // namespace metamodel
} // namespace q2d

#endif // COMPONENTCATEGORY_H
