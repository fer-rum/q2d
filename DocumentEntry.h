#ifndef DOCUMENTENTRY_H
#define DOCUMENTENTRY_H

#include "Enumerations.h"
#include "core/Identifiable.h"
#include "gui/SchematicElement.h"

#include <QGraphicsItem>
#include <QJsonObject>
#include <QObject>
#include <QString>

namespace q2d {

// forward declaration
class Document;

namespace model {
class Model;
class ModelElement;
}

/**
 * @brief The DocumentEntry class keeps a mapping between model and schematic elements
 * as well as the unique ids associated with them.
 *
 * DocumentEntry may have parents, to maintain potential hierarchical relations.
 */
class DocumentEntry
        : public QObject,
        public core::Identifiable {
    Q_OBJECT
private:
    enums::DocumentEntryType    m_type;
    model::ModelElement*        m_modelElement;
    gui::SchematicElement*      m_schematicElement;
    DocumentEntry*              m_parent;
    Document*                   m_document;

    /**
     * @brief chooseParentId is a helper method for correctly determining the parentId.
     * When given the choice between a parent DocumentEntries ID and a Documents ID,
     * the DocumentEntry will be preferred.
     * @param document
     * @param parentEntry
     * @return
     */
    static Identifiable* chooseParentIdentifier(Identifiable* document, Identifiable* parentEntry);

public:
    /**
     * @brief DocumentEntry is the minimal constructor.
     * @param id
     * @param type
     * @param parent
     */
    DocumentEntry(QString id,
                  enums::DocumentEntryType type,
                  Document* document,
                  DocumentEntry* parent = nullptr);

    // setter
    void setModelElement(model::ModelElement* modelElement);
    void setSchematicElement(gui::SchematicElement* schematicElement);

    // getter
    QString id() const;
    enums::DocumentEntryType type() const;
    model::ModelElement* modelElement() const;
    gui::SchematicElement* schematicElement() const;
    DocumentEntry* parent() const;
    Document* document() const;
    model::Model* model() const;
    gui::Schematic* scene() const;

signals:

private slots:
    void slot_updateToolTip();
};

} // namespace q2d
#endif // DOCUMENTENTRY_H
