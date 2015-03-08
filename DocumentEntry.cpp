#include "DocumentEntry.h"
#include "Document.h"
#include "Enumerations.h"
#include "model/ModelElement.h"

#include <QtDebug>

using namespace q2d;
using namespace q2d::gui;

DocumentEntry::DocumentEntry(QString id,
                             enums::DocumentEntryType type, Document* document,
                             DocumentEntry* parent) {
    Q_CHECK_PTR(document);
    Q_ASSERT(!id.isEmpty());
    // TODO better id validation

    m_id = id;
    m_type = type;
    m_modelElement = nullptr;
    m_schematicElement = nullptr;
    m_parent = parent;
    m_document = document;
}

void
DocumentEntry::setModelElement(model::ModelElement* modelElement){
    Q_CHECK_PTR(modelElement);
    m_modelElement = modelElement;
    m_modelElement->setRelatedEntry(this);
}

void
DocumentEntry::setSchematicElement(gui::SchematicsSceneChild* schematicElement){
    Q_CHECK_PTR(schematicElement);
    m_schematicElement = schematicElement;
}

QString
DocumentEntry::id() const {
    return m_id;
}

enums::DocumentEntryType
DocumentEntry::type() const {
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

Document*
DocumentEntry::document() const{
    return m_document;
}

model::Model*
DocumentEntry::model() const {
    return m_document->model();
}

gui::SchematicsScene*
DocumentEntry::scene() const{
    return m_document->schematic();
}
