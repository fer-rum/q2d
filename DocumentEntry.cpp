#include "DocumentEntry.h"
#include "Constants.h"
#include "model/ModelElement.h"

#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::gui;

DocumentEntry::DocumentEntry(QString id, DocumentEntryType type, model::ModelElement* modelElement,
              SchematicsSceneChild* schematicElement, DocumentEntry* parent){

    Q_ASSERT(!id.isEmpty());
    if(parent != nullptr){
        m_id = parent->id() + HIERARCHY_SEPERATOR + id;
    } else {
        m_id = id;
    }

    m_type = type;

    Q_CHECK_PTR(modelElement);
    this->m_modelElement = modelElement;

    Q_CHECK_PTR(schematicElement);
    this->m_schematicElement = schematicElement;

    this->m_parent = parent;

    qDebug() << "DocumentEntry " << id << " at " << schematicElement->scenePos()
                << " with parent " << (parent == nullptr? "null" : parent->id());
}

QString
DocumentEntry::id() const {
    return m_id;
}

model::ModelElement*
DocumentEntry::modelElement() const {
    return m_modelElement;
}

SchematicsSceneChild*
DocumentEntry::schematicElement() const {
    return m_schematicElement;
}

DocumentEntry*
DocumentEntry::parent() const {
    return m_parent;
}

QJsonObject*
DocumentEntry::toJson(){

    QJsonObject* result = new QJsonObject();

    // contain ID, ModelElement, SchematicItem
    // parent is implicitly given by the JSON document, this object will be passed into.

    result->insert(JSON_DOCENTRY_ID, QJsonValue(m_id));
    result->insert(JSON_DOCENTRY_SCHEMATIC_ELEMENT, QJsonValue(*(m_schematicElement->toJson())));

    // general type
    switch(m_type){
    case COMPONENT :
        result->insert(JSON_SCHEMATIC_TYPE_GENERAL, QJsonValue(GENERAL_TYPE_COMPONENT));
        break;
    case PORT :
        result->insert(JSON_SCHEMATIC_TYPE_GENERAL, QJsonValue(GENERAL_TYPE_PORT));
        break;
    case WIRE :
        result->insert(JSON_SCHEMATIC_TYPE_GENERAL, QJsonValue(GENERAL_TYPE_WIRE));
        break;
    default: break;
    }

    // TODO continue

    return result;
}
