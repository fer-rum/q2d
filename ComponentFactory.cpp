#include "ComponentFactory.h"

#include "ApplicationContext.h"
#include "ComponentCategory.h"
#include "ComponentType.h"
#include "Constants.h"

#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;

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
 * @param fileName is the name of the file that contains the component description as JSON
 * @param parent the parent category; May be null
 */
void
ComponentFactory::slot_loadType(QString fileName, ComponentCategory* parent){

    Q_ASSERT(!fileName.isEmpty());

    QFile* descriptionFile = new QFile(fileName);
    Q_ASSERT(descriptionFile->exists());

    // read the description file
    if(!descriptionFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "On loading component type: Could not open file "
                   << descriptionFile->fileName();
        return;
    }

    QFileInfo descriptionFileInfo = QFileInfo(*descriptionFile);
    QByteArray binaryData = descriptionFile->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(binaryData);
    descriptionFile->close();

    // If the file contains invalid JSON it simply creates a null document
    if(jsonDocument.isNull()){
        qDebug() << "JSON document seems to be invalid";
        return;
    }

    ComponentType* newType = this->createTypeFronJson(
                                 jsonDocument,
                                 descriptionFileInfo.absolutePath(),
                                 parent);
    Q_CHECK_PTR(newType);

    // TODO later disallow items w/o category
    if(parent != nullptr){
        parent->addSubItem(newType);
    } else {
        this->componentHierarchy.invisibleRootItem()->appendRow(newType);
    }
}

/**
 * @brief ComponentFactory::createTypeFronJson attempts to create a new ComponentType from its JSON-description.
 * @param jsonSource
 * @param basePath is the directory path in which the description resides. All paths in the JSON are treated as relative to this directory
 * @param parent
 * @return a pointer to the newly created ComponentType; a nullptr on failure
 */
ComponentType*
ComponentFactory::createTypeFronJson(
        const QJsonDocument jsonSource,
        const QString basePath,
        ComponentCategory* parent){

    Q_ASSERT(!jsonSource.isNull());
    QJsonObject jsonObject = jsonSource.object();

    // parse the name
    // defaults to "Unnamed"
    QJsonValue nameValue = jsonObject.value(JSON_COMPONENT_NAME);
    QString componentName = nameValue.toString(tr("Unnamed"));

    ComponentType* result = new ComponentType(componentName, parent);
    Q_CHECK_PTR(result);

    // load the symbol file
    // defaults to basePath/unknown.svg
    QJsonValue symbolPathValue = jsonObject.value(JSON_SYMBOL_PATH);
    QString symbolFilePath =  basePath + "/" + symbolPathValue.toString("unknown.svg");
    result->setSymbolPath(symbolFilePath);

    // read ports
    // defaults to an empty port array
    QJsonArray portArray = jsonObject.value(JSON_PORTS).toArray(QJsonArray());
    for(int index = 0; index < portArray.count(); ++index){
        QJsonValue currentValue = portArray[index];
        if(currentValue.isUndefined()) continue;
        QJsonObject portObject = currentValue.toObject();
        // port name
        QString portName = portObject.value(JSON_PORT_NAME)
                           .toString(tr("Unnamed"));
        // port position
        QJsonObject posObject = portObject.value(JSON_PORT_POSITION).toObject();
        int x = posObject.value(JSON_PORT_POSITION_X).toInt();
        int y = posObject.value(JSON_PORT_POSITION_Y).toInt();
        QPoint portPosition = QPoint(x, y);

        // port direction
        QString dirString = portObject.value(JSON_PORT_DIRECTION).toString("undef");
        model::PortDirection portDirection = model::portDirectionFromQString(dirString);

        result->addPort(portName, portPosition, portDirection);
    }

        // TODO read all the other stuff that might come in handy

    return result;
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
