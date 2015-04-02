#include "../Constants.h"
#include "../Enumerations.h"
#include "../DocumentEntry.h"
#include "../model/ModelElement.h"
#include "../model/Node.h"
#include "../model/Port.h"
#include "ToolTipFactory.h"

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::factories;
using namespace q2d::model;

QString
ToolTipFactory::toHtmlTable(const QMap<QString, QString> map){
    if(map.empty()){ return ""; }

    QString result;
    result += "<table>";

    QMapIterator<QString, QString> iter(map);
    while(iter.hasNext()){
        iter.next();
        result += "<tr><td>" + iter.key() + "</td><td>" + iter.value() + "</td></tr>";
    }

    result += "</table>";

    return result;
}

QMap<QString, QString>
ToolTipFactory::propertyMap(const ModelElement* source){
    Q_CHECK_PTR(source);

    QMap<QString, QString> properties = {
      {TOOLTIP_FULL_ID + ":", source->fullId()}
    };

    return properties;

}

QMap<QString, QString>
ToolTipFactory::propertyMap(const Node* source){

    model::ModelElement* driver = source->driver();

    QMap<QString, QString> properties = source->ModelElement::propertyMap();
    properties.insert(TOOLTIP_DRIVER + ":", (driver == nullptr? TOOLTIP_NONE : driver->fullId()));

    for (model::ModelElement * current : source->drivenElements()) {
        properties.insert(TOOLTIP_DRIVEN, current->fullId());
    }

    return properties;
}

QMap<QString, QString>
ToolTipFactory::propertyMap(const Port* source){

    QMap<QString, QString> properties = source->Node::propertyMap();
    properties.insert(TOOLTIP_DIRECTION + ":", model::enums::PortDirectionToString(source->direction()));

    return properties;
}

QString
ToolTipFactory::generateToolTip(DocumentEntry *entry){
    Q_CHECK_PTR(entry);

    // the tooltip header
    QString toolTipText = "<b>" + entry->localId() + "</b>";

    // the model elements part
    ModelElement* modelElement = entry->modelElement();
    if (modelElement != nullptr) {
        toolTipText.append("<hr>");
        toolTipText.append(toHtmlTable(modelElement->propertyMap()));
    }

    return toolTipText;
}
