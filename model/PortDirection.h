#ifndef PORTDIRECTION_H
#define PORTDIRECTION_H

#include <QString>

// TODO move the enum to Enumerations.h
// TODO move the functions to a model/Functions.h

namespace q2d {
namespace model {

enum PortDirection {
    IN,
    OUT,
    IN_OUT,
    UNSPECIFIED
};

PortDirection StringToPortDirection(const QString string);
QString PortDirectionToString(const PortDirection direction);

} // namespace model
} // namespce q2d

#endif // PORTDIRECTION_H
