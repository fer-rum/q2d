#include "../DocumentEntry.h"
#include "Model.h"
#include "ModelElement.h"
#include "../factories/ToolTipFactory.h"

using namespace q2d;
using namespace q2d::model;

ModelElement::ModelElement(DocumentEntry* relatedEntry)
    : QObject(relatedEntry->model()) {

    Q_CHECK_PTR(relatedEntry);
    Q_CHECK_PTR(relatedEntry->model());

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

QMap<QString, QString>
ModelElement::propertyMap() const {
    return factories::ToolTipFactory::propertyMap(this);
}
