#include "PortDirection.h"

using namespace q2d::model;

PortDirection
q2d::model::portDirectionFromQString(const QString string) {
    QString copy(string);

    copy = copy.trimmed().toLower();
    if(copy == "in") return PortDirection::IN;
    if(copy == "inout") return PortDirection::IN_OUT;
    if(copy == "out") return PortDirection::OUT;
    return PortDirection::UNSPECIFIED;
}
