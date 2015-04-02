#ifndef JSONHELPERS_H
#define JSONHELPERS_H

#include "metamodel/ConfigurationBitDescriptor.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QPointF>

namespace q2d {

// forward declarations
class Document;
class DocumentEntry;
class Project;

namespace gui {
class SchematicElement;
}

namespace metamodel {
class ConfigBitGroupDescriptor;
class PortDescriptor;
}

// TODO move this to namespace json
// TODO adapt naming





QJsonObject SchematicsSceneChildToJson(gui::SchematicElement* ssc);

// TODO include document name in JSON

namespace json {

void writeJsonFile(QString path, QJsonDocument doc);
QJsonDocument readJsonFile(QString path);

// json -> *
metamodel::ConfigBitGroupDescriptor* toConfigBitGroupDescriptor(QJsonObject json);
metamodel::PortDescriptor* toPortDescriptor(QJsonObject json);
QPoint toPoint(QJsonObject json);
QPointF toPointF(QJsonObject json);
Document* toDocument(QJsonObject json, QString name, Project* parent);

/**
 * @brief q2d::parseDocumentEntry
 * The parsed DocumentEntry will automatically be added to the given document.
 * @param json
 * @param document
 */
void toDocumentEntry(QJsonObject json, Document* document); // TODO should return DocumentEntry*

// TODO fix parameters
metamodel::ComponentDescriptor* toComponentDescriptor (
    const QJsonDocument jsonSource,
    const QString filePath,
    metamodel::Category* parent);

// * -> json
QJsonObject fromPoint(QPoint point);
QJsonObject fromPointF(QPointF point);
QJsonObject fromDocument(Document* doc);
QJsonObject fromDocumentEntry(DocumentEntry* entry);

} // namespace json
} // namespace q2d

#endif // JSONHELPERS_H
