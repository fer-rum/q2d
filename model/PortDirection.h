#ifndef PORTDIRECTION_H
#define PORTDIRECTION_H

#include <QString>

namespace q2d {
namespace model {

enum PortDirection {
    IN,
    OUT,
    IN_OUT,
    UNSPECIFIED
};

PortDirection portDirectionFromQString(const QString string);

} // namespace model
} // namespce q2d

#endif // PORTDIRECTION_H
