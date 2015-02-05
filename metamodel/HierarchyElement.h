#ifndef COMPONENTDESCRIPTOR_H
#define COMPONENTDESCRIPTOR_H

#include "Element.h"

#include <QGraphicsSvgItem>

namespace q2d {
namespace metamodel {

// forward declaration
class Category;

/**
 * @brief The HierarchyElement class is the superclass for the things that make out the component hierarchy,
 * i.e. Categories and Types.
 * HierarchyElement-objects do have a hierarchy name besides the usual one.
 */
class HierarchyElement :
    public Element {
public:
    explicit HierarchyElement(QString name, Category* parent = nullptr);

    virtual HierarchyElement* parent() const;
    virtual void setParent(HierarchyElement* parent);

    virtual int type() const override = 0;
    QString hierarchyName();
};

} // namespace metamodel
} // namespace q2d

// Metatype declaration
Q_DECLARE_METATYPE(QGraphicsSvgItem*)  // for circuit symbols
// TODO is this still used?

#endif // COMPONENTDESCRIPTOR_H
