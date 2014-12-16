#include "ComponentType.h"

using namespace q2d;

/**
 * @brief ComponentType::ComponentType
 * If the symbol is null, no icon will be set.
 *
 * @param name
 * @param symbol ; May be null
 *
 * Assumption: name is not empty
 */
ComponentType::ComponentType(QString name, QGraphicsSvgItem* symbol) :
    QStandardItem(name) {

    Q_ASSERT(!name.isEmpty());
    // FIXME: allowing the symbol to be null is only for testing purposes

    this->symbol = symbol;

    // TODO see if this works
    // Create Icon for UI from Svg

    if(symbol != nullptr){
        QSvgRenderer svgRenderer(symbol);
        QPixmap* iconPixmap = new QPixmap(svgRenderer.defaultSize());
        QPainter* pixmapPainter = new QPainter(iconPixmap);
        svgRenderer.render(pixmapPainter);
        QIcon icon(*iconPixmap);
        this->setIcon(icon);
        // TODO possible memory leak
        // find all above objects that are no longer referenced after setting the icon
    }
}

ComponentCategory::ComponentCategory(QString name) :
    QStandardItem(name) {}

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
