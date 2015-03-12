#ifndef DOCUMENTENTRY_H
#define DOCUMENTENTRY_H

#include "Enumerations.h"
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
    : public QObject {
    Q_OBJECT
private:
    QString                     m_id;
    enums::DocumentEntryType    m_type;
    model::ModelElement*        m_modelElement;
    gui::SchematicElement*      m_schematicElement;
    DocumentEntry*              m_parent;
    Document*                   m_document;

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
