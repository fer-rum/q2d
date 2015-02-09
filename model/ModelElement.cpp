#include "../DocumentEntry.h"
#include "Model.h"
#include "ModelElement.h"

using namespace q2d;
using namespace q2d::model;

ModelElement::ModelElement(Model* parent, DocumentEntry* relatedEntry)
    : QObject(parent) {
    m_relatedEntry = relatedEntry;
}

DocumentEntry*
ModelElement::relatedEntry() const {
    return m_relatedEntry;
}

void
ModelElement::setRelatedEntry(DocumentEntry* relatedEntry) {
    m_relatedEntry = relatedEntry;
}

Model*
ModelElement::model() const {
    return qobject_cast<Model*>(this->parent());
}
