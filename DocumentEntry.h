#ifndef DOCUMENTENTRY_H
#define DOCUMENTENTRY_H

#include "Enumerations.h"
#include "gui/SchematicsSceneChild.h"

#include <QGraphicsItem>
#include <QJsonObject>
#include <QString>

namespace q2d {

// forward declaration
class Document;

namespace model {
class ModelElement;
}

/**
 * @brief The DocumentEntry class keeps a mapping between model and schematic elements
 * as well as the unique ids associated with them.
 *
 * DocumentEntry may have parents, to maintain any potential hierarchical relations.
 */
class DocumentEntry {
private:
    QString                     m_id;
    enums::DocumentEntryType    m_type;
    model::ModelElement*        m_modelElement;
    gui::SchematicsSceneChild*  m_schematicElement;
    DocumentEntry*              m_parent;
public:
    DocumentEntry(QString id,
                  enums::DocumentEntryType type,
                  model::ModelElement* modelElement,
                  gui::SchematicsSceneChild* schematicElement,
                  DocumentEntry* parent = nullptr);
    QString id() const;
    enums::DocumentEntryType type();
    model::ModelElement* modelElement() const;
    gui::SchematicsSceneChild* schematicElement() const;
    DocumentEntry* parent() const;
};

} // namespace q2d
#endif // DOCUMENTENTRY_H
