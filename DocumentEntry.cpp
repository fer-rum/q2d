#include "DocumentEntry.h"
#include "Document.h"
#include "Enumerations.h"
#include "Constants.h"
#include "model/ModelElement.h"

#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::gui;

DocumentEntry::DocumentEntry(QString id, enums::DocumentEntryType type,
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

enums::DocumentEntryType
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
