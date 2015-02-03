#ifndef COMPONENTDESCRIPTOR_H
#define COMPONENTDESCRIPTOR_H

#include "Enumerations.h"

#include <QGraphicsSvgItem>
#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

// forward declaration
class ComponentCategory;

class ComponentDescriptor :
    public QObject,
    public QStandardItem {
    Q_OBJECT
public:
    explicit ComponentDescriptor(QString name, ComponentCategory* parent = 0);

    virtual int type() const = 0;
    QString hierarchyName();
};

} // namespace metamodel
} // namespace q2d

// Metatype declaration
Q_DECLARE_METATYPE(QGraphicsSvgItem*)  // for circuit symbols
// TODO is this still used?

#endif // COMPONENTDESCRIPTOR_H
