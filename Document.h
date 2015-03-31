#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "DocumentEntry.h"
#include "core/Identifiable.h"
#include "model/Model.h"
#include "gui/Schematic.h"
#include "metamodel/ComponentDescriptor.h"

#include <QDir>
#include <QObject>
#include <QStandardItem>
#include <QString>

namespace q2d {

// forward declaration
class ComponentFactory;
class Project;

namespace gui {
class ComponentGraphicsItem;
}

enum DocumentRole {
    MODEL = Qt::UserRole + 1000,
    SCHEMATIC = Qt::UserRole + 1001
};

// TODO documentation
// TODO referenced Documents?
/**
 * @brief Document::Document
 *
 * Upon creation of a document an empty described model
 * and an empty schematic view are created.
 *
 * @param name is the name of the document and also the name of the component
 * which is described by the document.
 * It also serves as the root of all IDs of elements contained in the document.
 *
 * @param parent the Project the document belongs to; Must not be null,
 * since the component factory is cached from it
 */
class Document :
    public QObject,
    public QStandardItem,
    public core::Identifiable {
    Q_OBJECT
private:
    /**
     * @brief componentFactory is a cached pointer to the
     * ComponentFactory instance.
     */
    ComponentFactory* m_componentFactory;

    /**
     * @brief m_entries keeps all the relations between model and
     * schematic elements.
     */
    QList<DocumentEntry*> m_entries;

    void addComponentPorts(metamodel::ComponentDescriptor* type,
                           DocumentEntry* parentEntry);

public:
    explicit Document(QString name, Project* parent);

    gui::Schematic* schematic();
    model::Model* model() const;
    ComponentFactory* componentFactory() const;

    // TODO rename: instantiateComponent?
    void addComponent(QString typeId, QPoint position);
    void addWire(QString senderNodeId, QString receiverNodeId);
    void addInputPort(QString id, QPointF pos);
    void addOutputPort(QString id, QPointF pos);

    // intended for loading a document from Json
    void addEntry(DocumentEntry* entry);

    // access helpers
    DocumentEntry* entryForFullId(const QString fullId) const;

    QList<DocumentEntry*> entries() const;

    void save(QDir saveDir);
};

} // namespace q2d

// metatype declaration for the contents of the document
// so these things can be used as data
Q_DECLARE_METATYPE(q2d::model::Model*)
Q_DECLARE_METATYPE(q2d::gui::Schematic*)

#endif // DOCUMENT_H
