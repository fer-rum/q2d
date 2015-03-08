#include "Enumerations.h"

using namespace q2d;
using namespace q2d::enums;


// initialize the mappings from enums to strings
QMap<DocumentEntryType, QString>
q2d::enums::map_DocumentEntryType {
    {DocumentEntryType::COMPONENT,      "component"     },
    {DocumentEntryType::COMPONENT_PORT, "component_port"},
    {DocumentEntryType::OUTSIDE_PORT,   "outside_port"  },
    {DocumentEntryType::WIRE,           "wire"          },
    {DocumentEntryType::UNDEFINED,      "undefined"     }
};

QString
q2d::enums::DocumentEntryTypeToString(const DocumentEntryType type) {
    if (map_DocumentEntryType.contains(type)) {
        return map_DocumentEntryType[type];
    } else {
        return map_DocumentEntryType[DocumentEntryType::UNDEFINED];
    }
}


DocumentEntryType
q2d::enums::StringToDocumentEntryType(const QString string) {

    QString lookup = string.trimmed().toLower();
    return map_DocumentEntryType.key(lookup, DocumentEntryType::UNDEFINED);
}

int
metamodel::enums::elementTypeToInt(ElementType t) {
    return (int)t;
}

metamodel::enums::ElementType
metamodel::enums::intToElementType(int i) {
    switch (i) {
    case (int)ElementType::CATEGORY :
        return ElementType::CATEGORY;
    case (int)ElementType::COMPONENT :
        return ElementType::COMPONENT;
    case (int)ElementType::CONFIG_BIT_GROUP :
        return ElementType::CONFIG_BIT_GROUP;
    case (int) ElementType::CONFIG_BIT :
        return ElementType::CONFIG_BIT;
    case (int)ElementType::PORT :
        return ElementType::PORT;
    default :
        return ElementType::INVALID;
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

model::enums::PortDirection
model::enums::invert(const PortDirection initial){
    switch(initial){
    case PortDirection::IN :
        return PortDirection::OUT;
    case PortDirection::OUT:
        return PortDirection::IN;
    default:
        return PortDirection::UNSPECIFIED;
    }
}
