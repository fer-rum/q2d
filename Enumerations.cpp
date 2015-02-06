#include "Enumerations.h"

using namespace q2d;

int
metamodel::enums::elementTypeToInt(ElementType t) {
    return (int)t;
}

metamodel::enums::ElementType
metamodel::enums::intToElementType(int i) {
    switch(i) {
    case (int)ElementType::CATEGORY :           return ElementType::CATEGORY;
    case (int)ElementType::COMPONENT :          return ElementType::COMPONENT;
    case (int)ElementType::CONFIG_BIT_GROUP :   return ElementType::CONFIG_BIT_GROUP;
    case (int) ElementType::CONFIG_BIT :        return ElementType::CONFIG_BIT;
    case (int)ElementType::PORT :               return ElementType::PORT;
    default :                                   return ElementType::INVALID;
    }
}

model::enums::PortDirection
model::enums::StringToPortDirection(const QString string) {
    QString copy(string);

    copy = copy.trimmed().toLower();
    if (copy == "in") {
        return PortDirection::IN;
    }
    if (copy == "inout") {
        return PortDirection::IN_OUT;
    }
    if (copy == "out") {
        return PortDirection::OUT;
    }
    return PortDirection::UNSPECIFIED;
}


QString
model::enums::PortDirectionToString(const PortDirection direction) {
    switch (direction) {
    case PortDirection::IN :
        return "in";
    case PortDirection::OUT :
        return "out";
    case PortDirection::IN_OUT :
        return "inout";
    default:
        return "unspecified";
    }
}
