#include "DocumentEntry.h"

#include "Constants.h"
#include "model/ModelElement.h"

using namespace q2d;
using namespace q2d::constants;

DocumentEntry::DocumentEntry(QString id, model::ModelElement* modelElement,
              QGraphicsItem* schematicElement, DocumentEntry* parent){

    Q_ASSERT(!id.isEmpty());
    if(parent != nullptr){
        this->m_id = parent->id() + HIERARCHY_SEPERATOR + id;
    } else {
        this->m_id = id;
    }

    Q_CHECK_PTR(modelElement);
    this->m_modelElement = modelElement;

    Q_CHECK_PTR(schematicElement);
    this->m_schematicElement = schematicElement;

    this->m_parent = parent;
}

QString
DocumentEntry::id() const {
    return m_id;
}

model::ModelElement*
DocumentEntry::modelElement() const {
    return m_modelElement;
}

QGraphicsItem*
DocumentEntry::schematicElement() const {
    return m_schematicElement;
}

DocumentEntry*
DocumentEntry::parent() const {
    return m_parent;
}
