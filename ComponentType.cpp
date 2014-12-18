#include "ComponentType.h"

using namespace q2d;

ComponentDescriptor::ComponentDescriptor(QString name, QObject* parent) :
    QObject(parent), // TODO rethink this
    QStandardItem(name){}

/**
 * @brief ComponentType::ComponentType
 * If the symbol is null, no icon will be set.
 *
 * @param name
 * @param symbol ; May be null
 *
 * Assumption: name is not empty
 */
ComponentType::ComponentType(QString name, QObject* parent) :
    ComponentDescriptor(name, parent) {

    // TODO build and set icon somewhere
//    Q_ASSERT(!name.isEmpty());
//    // FIXME: allowing the symbol to be null is only for testing purposes

//    this->symbol = symbol;

//    // TODO see if this works
//    // Create Icon for UI from Svg

//    if(symbol != nullptr){
//        QSvgRenderer svgRenderer(symbol);
//        QPixmap* iconPixmap = new QPixmap(svgRenderer.defaultSize());
//        QPainter* pixmapPainter = new QPainter(iconPixmap);
//        svgRenderer.render(pixmapPainter);
//        QIcon icon(*iconPixmap);
//        this->setIcon(icon);
//        // TODO possible memory leak
//        // find all above objects that are no longer referenced after setting the icon
//    }
}

ComponentCategory::ComponentCategory(QString name, QObject* parent) :
    ComponentDescriptor(name, parent) {}

ComponentCategory::~ComponentCategory (){
    // TODO check if sub-items get destroyed properly
}

void
ComponentCategory::addSubCategory (ComponentCategory *toAdd){

    Q_CHECK_PTR(toAdd);

    this->appendRow (toAdd);
}

void
ComponentCategory::addComponentType (ComponentType *toAdd){

    Q_CHECK_PTR(toAdd);

    this->appendRow (toAdd);
}

ComponentFactory::ComponentFactory(){}

ComponentFactory::~ComponentFactory (){}

/**
 * @brief ComponentFactory::addCategory creates a new category and adds it to
 * the component hierarchy.
 * If the parent category is null, the item will be sorted directly below the
 * root.
 *
 * @param name
 * @param parent the parent category; May be null
 */
void
ComponentFactory::addCategory(QString name, ComponentCategory* parent){
    // TODO ensure update signals are fired upon adding a category

    Q_ASSERT(!name.isEmpty ());

    ComponentCategory* newCategory = new ComponentCategory(name);

    if(parent == nullptr){
        this->componentHierarchy.invisibleRootItem()->appendRow(newCategory);
    } else {
        parent->addSubCategory(newCategory);
    }
}

/**
 * @brief ComponentFactory::addType creates a new component type and adds it to
 * the component hierarchy.
 * If the parent category is null, the item will be sorted directly below the
 * root.
 *
 * @param name
 * @param parent the parent category; May be null
 */
void
ComponentFactory::addType(QString name, ComponentCategory* parent){
    // TODO ensure update signals are fired upon adding a category

    Q_ASSERT(!name.isEmpty ());

    ComponentCategory* newCategory = new ComponentCategory(name);

    if(parent == nullptr){
        this->componentHierarchy.invisibleRootItem()->appendRow(newCategory);
    } else {
        parent->addSubCategory(newCategory);
    }
}

/**
 * @brief ComponentFactory::getCategoryForIndex attempts to get the ComponentCategory
 * for the given index.
 *
 * If the index is invalid or the indexed element is not a ComponentCategory, a nullptr will be returned.
 *
 * @param index
 * @return ; May return null
 */
ComponentCategory*
ComponentFactory::getCategoryForIndex(const QModelIndex &index){
    if(!index.isValid()){
        return nullptr;
    }

    QStandardItem* item = this->componentHierarchy.itemFromIndex(index);
    return static_cast<ComponentCategory*>(item);
}

/**
 * @brief ComponentFactory::getTypeForIndex attempts to get the ComponentType
 * for the given index.
 *
 * If the index is invalid or the indexed element is not a ComponentType, a nullptr will be returned.
 *
 * @param index
 * @return ; May return null
 */
ComponentType*
ComponentFactory::getTypeForIndex(const QModelIndex &index){

    if(!index.isValid()){
        return nullptr;
    }

    QStandardItem* item = this->componentHierarchy.itemFromIndex(index);
    return static_cast<ComponentType*>(item);
}

QStandardItemModel*
ComponentFactory::getComponentHierarchy(){
    return &(this->componentHierarchy);
}
