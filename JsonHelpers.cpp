#include "JsonHelpers.h"

#include "ComponentFactory.h"
#include "Constants.h"
#include "Document.h"
#include "DocumentEntry.h"
#include "Project.h"
#include "gui/ComponentGraphicsItem.h"
#include "gui/SchematicsSceneChild.h"
#include "model/ModelElement.h"
#include "metamodel/ComponentDescriptor.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

using namespace q2d::constants;
using namespace q2d::json;

void
q2d::json::writeJsonFile(QString path, QJsonDocument doc) {

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}

/**
 * @brief q2d::json::readJsonFile attempts to read a given file.
 * If for some reason the reading fails, an empty document will be returned.
 * The validity of the read QJsonDocument has to be checked by the caller.
 * @param path
 * @return
 */
QJsonDocument
q2d::json::readJsonFile(QString path){
    const QString logPrefix = "ReadJsonFile(" + path + ")";

    if(path.isEmpty()){
        qWarning() << logPrefix << "file path was empty";
    }

    QFile jsonFile(path);
    if(!jsonFile.exists()){
        qWarning() << logPrefix << "file does not exist";
    }

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << logPrefix << "could not open file";
        return QJsonDocument();
    }

    QByteArray rawText = jsonFile.readAll();
    QJsonDocument result = QJsonDocument::fromJson(rawText);
    jsonFile.close();

    qDebug() << logPrefix << "successfully read file";

    return result;
}

QJsonObject
q2d::json::fromPointF(QPointF point) {
    Q_ASSERT(!point.isNull());

    QJsonObject result = QJsonObject();

    result.insert(JSON_GENERAL_POSITION_X, QJsonValue(point.x()));
    result.insert(JSON_GENERAL_POSITION_Y, QJsonValue(point.y()));

    return result;
}

QPointF
q2d::json::toPointF(QJsonObject json) {
    Q_ASSERT(json.contains(JSON_GENERAL_POSITION_X));
    Q_ASSERT(json.contains(JSON_GENERAL_POSITION_Y));

    float x = json.value(JSON_GENERAL_POSITION_X).toInt();
    float y = json.value(JSON_GENERAL_POSITION_Y).toInt();

    return QPointF(x, y);
}

QJsonObject
q2d::json::fromDocument(Document* doc) {

    QJsonArray entriesArray = QJsonArray();

    // Write the entries
    for (DocumentEntry * entry : doc->entries()) {
        entriesArray.append(QJsonValue(DocumentEntryToJson(entry)));
    }

    QJsonObject entriesWrapper = QJsonObject();
    entriesWrapper.insert(JSON_DOCENTRY, entriesArray);

    return entriesWrapper;
}

/**
 * @brief q2d::json::toDocument creates a new Document from the JSON representation.
 * The resulting document will have no parent set, this has to be done by the caller himself.
 * @param json
 * @param name
 * @param parent
 * @return
 */
q2d::Document*
q2d::json::toDocument(QJsonObject json, QString name, Project* parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    Document* doc =  new Document(name, parent);

    QJsonArray entries = json.value(JSON_DOCENTRY).toArray();

    // Read the entries
    for (QJsonValue jsonEntry : entries) {
        parseDocumentEntry(jsonEntry.toObject(), doc);
    }

    return doc;
}

QJsonObject
q2d::DocumentEntryToJson(DocumentEntry* entry) {
    Q_CHECK_PTR(entry);

    QJsonObject result = QJsonObject();

    // contain ID, ModelElement, SchematicItem, type, parent entry
    // parentDocument is implicitly given by the JSON document,
    // this object will be passed into.

    result.insert(JSON_DOCENTRY_ID, QJsonValue(entry->id()));
    result.insert(JSON_DOCENTRY_SCHEMATIC_ELEMENT,
                  QJsonValue(SchematicsSceneChildToJson(
                                 entry->schematicElement())));

    // general type
    result.insert(JSON_DOCENTRY_TYPE,
                  QJsonValue(DocumentEntryTypeToString(entry->type())));
    // the parent id, if there is one
    if (entry->parent() != nullptr) {
        result.insert(JSON_DOCENTRY_PARENT, QJsonValue(entry->parent()->id()));
    } else {
        result.insert(JSON_DOCENTRY_PARENT, QJsonValue::Null);
    }

    // TODO is there something about the model to save?

    return result;
}

/**
 * @brief q2d::parseDocumentEntry
 * The parsed DocumentEntry will automatically be added to the given document.
 * @param json
 * @param document
 */
void
q2d::parseDocumentEntry(QJsonObject json, Document* document) {
    Q_ASSERT(json.contains(JSON_DOCENTRY_ID));

    QString id = json.value(JSON_DOCENTRY_ID).toString();
    QString typeString = json.value(JSON_DOCENTRY_TYPE).toString();
    DocumentEntryType type = StringToDocumentEntryType(typeString);

    qDebug() << "Parsing document entry" << id << "of type" << typeString;

    // TODO reconstruct the schematics element
    QJsonObject schematicJson =
        json.value(JSON_DOCENTRY_SCHEMATIC_ELEMENT).toObject();
    QString typeId = schematicJson.value(JSON_SCHEMATIC_SUB_TYPE).toString();
    QPointF position = toPointF(
                           schematicJson.value(JSON_SCHEMATIC_POSITION).toObject());

    // reconstruct the parent
    QJsonValue parentValue = json.value(JSON_DOCENTRY_PARENT);
    DocumentEntry* parent;
    if (parentValue.isNull()) {
        parent = nullptr;
    } else {
        parent = document->entry(parentValue.toString());
    }

    switch (type) {
    case COMPONENT :
        document->componentFactory()->instantiateComponent(
            document, typeId, position, id);
        break;
    case PORT : {
        QString directionString = schematicJson.value(JSON_SCHEMATIC_SUB_TYPE).toString();
        document->componentFactory()->instantiatePort(
            document, parent, position, model::enums::StringToPortDirection(directionString), id);
    }
    break;
    case WIRE : {
        QJsonObject additional = schematicJson.value(JSON_SCHEMATIC_ADDITIONAL).toObject();
        Q_ASSERT(!additional.isEmpty());

        DocumentEntry* sender = document->entry(additional.value(JSON_WIRE_START).toString());
        Q_CHECK_PTR(sender);

        DocumentEntry* receiver = document->entry(additional.value(JSON_WIRE_END).toString());
        Q_CHECK_PTR(receiver);

        document->componentFactory()->instantiateWire(document, sender, receiver, id);
    }
    break;
    default:
        ;
        // ignore everything else for now
    }


}

QJsonObject
q2d::SchematicsSceneChildToJson(gui::SchematicsSceneChild* ssc) {
    QJsonObject result = QJsonObject();

    result.insert(JSON_SCHEMATIC_SUB_TYPE, QJsonValue(ssc->specificType()));
    result.insert(JSON_SCHEMATIC_POSITION, fromPointF(ssc->pos()));

    QJsonObject additionalInfo = ssc->additionalJson();
    if (!additionalInfo.isEmpty()) {
        result.insert(JSON_SCHEMATIC_ADDITIONAL, QJsonValue(additionalInfo));
    }

    return result;
}


q2d::metamodel::ConfigBitGroupDescriptor*
q2d::json::toConfigBitGroupDescriptor(QJsonObject json){
    Q_ASSERT(!json.isEmpty());
    Q_ASSERT(json.contains(JSON_GENERAL_NAME));
    Q_ASSERT(json.contains(JSON_GENERAL_SIZE));

    QString groupName   = json.value(JSON_GENERAL_NAME).toString();
    int     memberCount = json.value(JSON_GENERAL_SIZE).toInt();

    Q_ASSERT(!groupName.isEmpty());
    Q_ASSERT(memberCount > 0);

    return new metamodel::ConfigBitGroupDescriptor(groupName, memberCount);
}


/**
 * @brief ComponentFactory::createTypeFronJson attempts to create a new ComponentType from its JSON-description.
 * @param jsonSource
 * @param filePath is the path of the descriptor file.
 * All paths in the JSON are treated as relative to its base directory
 * @param parent
 * @return a pointer to the newly created ComponentType; a nullptr on failure
 */
q2d::metamodel::ComponentDescriptor*
q2d::json::toComponentDescriptor (
    const QJsonDocument jsonSource,
    const QString filePath,
    q2d::metamodel::Category* parent) {

    // extract the base directory path from the file path
    QString fileName = filePath.split(QDir::separator()).last();
    QString baseDirPath = QString(filePath);
    baseDirPath.chop(fileName.size());

    Q_ASSERT(!jsonSource.isNull());
    QJsonObject jsonObject = jsonSource.object();

    // parse the name
    QJsonValue nameValue = jsonObject.value(JSON_GENERAL_NAME);
    QString componentName = nameValue.toString();
    Q_ASSERT(!componentName.isEmpty());

    q2d::metamodel::ComponentDescriptor* result =
            new q2d::metamodel::ComponentDescriptor(componentName, parent);
    Q_CHECK_PTR(result);
    result->setDescriptorPath(filePath);

    // load the symbol file
    // defaults to basePath/unknown.svg
    QJsonValue symbolPathValue = jsonObject.value(JSON_SYMBOL_PATH);
    QString symbolFilePath =
            baseDirPath + QDir::separator() + symbolPathValue.toString("unknown.svg");
    result->setSymbolPath(symbolFilePath);

    // read ports
    // defaults to an empty port array
    QJsonArray portArray = jsonObject.value(JSON_PORTS).toArray(QJsonArray());
    for(QJsonValue currentValue : portArray) {
        if (currentValue.isUndefined()) {
            continue;
        }
        QJsonObject     portObject      = currentValue.toObject();
        QJsonObject     posObject       = portObject.value(JSON_GENERAL_POSITION).toObject();
        QString         portName        = portObject.value(JSON_GENERAL_NAME).toString();
        QString         dirString       = portObject.value(JSON_PORT_DIRECTION).toString();
        QPointF         portPosition    = json::toPointF(posObject);
        model::enums::PortDirection portDirection = model::enums::StringToPortDirection(dirString);

        result->addPort(portName, portPosition, portDirection);
    }

    // get the config bits if there are some
    if(jsonObject.contains(JSON_CONFIG_BIT_GROUP)){
        QJsonArray configBitsJson = jsonObject.value(JSON_CONFIG_BIT_GROUP).toArray();
        for(QJsonValue currentGroup : configBitsJson){
            q2d::metamodel::ConfigBitGroupDescriptor* configBits =
                    json::toConfigBitGroupDescriptor(currentGroup.toObject());
            Q_CHECK_PTR(configBits);
            // TODO instead print a proper warning
            result->addConfigBitGroup(configBits);
        }
    }

    return result;
}
