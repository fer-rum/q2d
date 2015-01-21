#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "DocumentEntry.h"
#include "model/Model.h"
#include "gui/SchematicsScene.h"
#include "metamodel/ComponentType.h"

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
//     - controller in MVC
// TODO referenced Documents?
// TODO description text
// TODO saving
// TODO loading
// TODO association between Schematic and Model elements

class Document :
        public QObject,
        public QStandardItem {
    Q_OBJECT
private:
    /**
     * @brief componentFactory is a cached pointer to the ComponentFactory instance.
     */
    ComponentFactory* componentFactory;

    /**
     * @brief m_entries keeps all the relations between model and schematic elements.
     */
    QList<DocumentEntry*> m_entries;

    void addComponentPorts(metamodel::ComponentType* type,
                           QString componentId,
                           model::Component* modelComponent,
                           q2d::gui::ComponentGraphicsItem* schematicComponent);



public:
    explicit Document(QString name, Project* parent);

    gui::SchematicsScene* schematic();
    model::Model* model();

    // TODO rename: instantiateComponent?
    void addComponent(QString path, QPoint position);
    void addWire(QString senderNodeId, QString receiverNodeId);

    // access helpers
    DocumentEntry* entry(const QString id) const;
    DocumentEntry* entry(const QGraphicsItem* schematicElement) const;
    DocumentEntry* entry(const model::ModelElement* modelElement) const;
};

} // namespace q2d

// metatype declaration for the contents of the document
// so these things can be used as data
Q_DECLARE_METATYPE(q2d::model::Model*)
Q_DECLARE_METATYPE(q2d::gui::SchematicsScene*)

#endif // DOCUMENT_H
