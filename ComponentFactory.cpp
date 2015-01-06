#include "ComponentFactory.h"

#include "ApplicationContext.h"
#include "ComponentCategory.h"
#include "ComponentType.h"

#include <QtDebug>

using namespace q2d;

ComponentFactory::ComponentFactory(ApplicationContext* parent)
    : QObject(parent){}

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
ComponentFactory::slot_addCategory(QString name, ComponentCategory* parent){
    // TODO ensure update signals are fired upon adding a category

    Q_ASSERT(!name.isEmpty ());

    ComponentCategory* newCategory = new ComponentCategory(name);

    if(parent == nullptr){
        this->componentHierarchy.invisibleRootItem()->appendRow(newCategory);
    } else {
        parent->addSubItem(newCategory);
    }
}

/**
 * @brief ComponentFactory::slot_loadType creates a new component type and adds it to
 * the component hierarchy.
 * If the parent category is null, the item will be sorted directly below the
 * root.
 *
 * @param name
 * @param parent the parent category; May be null
 */
void
ComponentFactory::slot_loadType(QString fileName, ComponentCategory* parent){

    qDebug() << "Requested loading component type " << fileName << " with parent " << (parent == nullptr? "none" : parent->text());



    ComponentType* newType = new ComponentType(fileName, parent);
    Q_CHECK_PTR(newType);

    // TODO later disallow items w/o category
    if(parent != nullptr){
        parent->addSubItem(newType);
    } else {
        this->componentHierarchy.invisibleRootItem()->appendRow(newType);
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
    return dynamic_cast<ComponentCategory*>(item);
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
