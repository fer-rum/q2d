#include "DocumentEntry.h"
#include "Document.h"
#include "Constants.h"
#include "model/ModelElement.h"

#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::gui;

QString
q2d::DocumentEntryTypeToString(DocumentEntryType type) {

    switch (type) {
    case COMPONENT :
        return GENERAL_TYPE_COMPONENT;
    case PORT :
        return GENERAL_TYPE_PORT;
    case WIRE :
        return GENERAL_TYPE_WIRE;
    default :
        return GENERAL_TYPE_UNDEFINED;
    }
}

// TODO constness
DocumentEntryType
q2d::StringToDocumentEntryType(QString string) {

    string = string.trimmed().toLower();

    if (string == GENERAL_TYPE_COMPONENT) {
        return DocumentEntryType::COMPONENT;
    }
    if (string == GENERAL_TYPE_PORT) {
        return DocumentEntryType::PORT;
    }
    if (string == GENERAL_TYPE_WIRE) {
        return DocumentEntryType::WIRE;
    }
    return DocumentEntryType::UNDEFINED;
}

DocumentEntry::DocumentEntry(QString id, DocumentEntryType type,
                             model::ModelElement* modelElement,
                             SchematicsSceneChild* schematicElement,
                             DocumentEntry* parent) {

    Q_ASSERT(!id.isEmpty());
    Q_CHECK_PTR(modelElement);
    Q_CHECK_PTR(schematicElement);
    m_id = id;
    m_type = type;
    m_modelElement = modelElement;
    m_schematicElement = schematicElement;
    m_parent = parent;

    modelElement->setRelatedEntry(this);

    qDebug() << "DocumentEntry " << id << " at " << schematicElement->scenePos()
             << " with parent " << (parent == nullptr ? "null" : parent->id());
}

QString
DocumentEntry::id() const {
    return m_id;
}

DocumentEntryType
DocumentEntry::type() {
    return m_type;
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
