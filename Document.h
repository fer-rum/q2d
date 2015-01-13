#ifndef DOCUMENT_H
#define DOCUMENT_H

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

class Document :
        public QObject,
        public QStandardItem {
    Q_OBJECT
private:

        ComponentFactory* componentFactory;

public:
    explicit Document(QString name, Project* parent);

    gui::SchematicsScene* getSchematic();
    model::Model* getDescribedModel();

    // TODO rename: instantiateComponent
    void addComponent(QString path, QPoint position);
};

} // namespace q2d

// metatype declaration for the contents of the document
// so these things can be used as data
Q_DECLARE_METATYPE(q2d::model::Model*)
Q_DECLARE_METATYPE(q2d::gui::SchematicsScene*)

#endif // DOCUMENT_H
