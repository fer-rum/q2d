#include "Document.h"

#include "gui/SchematicsScene.h"
#include "ApplicationContext.h"
#include "ComponentFactory.h"
#include "Project.h"

using namespace q2d;

/**
 * @brief Document::Document
 *
 * Upon creation of a document a empty described model
 * and an empty schematic view are created.
 *
 * @param name is the name of the document and also the name of the component
 * which is described by the document.
 *
 * @param parent the Project the document belongs to; Must not be null.
 */
Document::Document(QString name, Project* parent) :
    QObject(parent),
    QStandardItem(name) {

        Q_CHECK_PTR(parent);

    // obtain the component factory
    ApplicationContext* context = dynamic_cast<ApplicationContext*>(parent->parent());
    Q_CHECK_PTR(context);
    this->componentFactory = context->getComponentFactory();

    this->setData(QVariant::fromValue(new model::Model()), DocumentRole::MODEL);
    this->setData(QVariant::fromValue(new gui::SchematicsScene(this)), DocumentRole::SCHEMATIC);
}

/**
 * @brief Document::getSchematicView is a getter for convenience
 * @return
 */
gui::SchematicsScene*
Document::getSchematic(){
    return this->data(DocumentRole::SCHEMATIC).value<gui::SchematicsScene*>();
}

/**
 * @brief Document::getDescribedModel is a convenience function
 * @return
 */
model::Model*
Document::getDescribedModel(){
    return this->data(DocumentRole::MODEL).value<model::Model*>();
}

/**
 * @brief Document::addComponent instantiates a new component from a ComponentType,
 * givwn by its path in the component hierarchy.
 * The new component will be placed at the given position in the schematic.
 *
 * @param path is the path of the ComponentType in the component hierarchy.
 * @param position of the component at which it is placed in the schematic.
 */
void
Document::addComponent(QString path, QPoint position){

    // get needed information from the ComponentFactory
    ComponentType* type = this->componentFactory->getTypeForHierarchyName(path);

    // add graphics to Schematic
    QGraphicsSvgItem* image = new QGraphicsSvgItem(type->symbolPath());

    image->setPos(position);
    image->setFlag(QGraphicsItem::ItemIsMovable);

    this->getSchematic()->addItem(image);

    // TODO add Component to model
}
