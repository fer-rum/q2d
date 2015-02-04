#ifndef JSONHELPERS_H
#define JSONHELPERS_H

#include "Document.h"
#include "DocumentEntry.h"

#include <QJsonObject>
#include <QPointF>

namespace q2d {

// forward declarations
namespace metamodel {
class ConfigBitGroupDescriptor;
}
// TODO move this to namespace json
// TODO adapt naming
void WriteJsonFile(QString path, QJsonDocument doc);

QJsonObject PointFToJson(QPointF point);
QPointF JsonToPointF(QJsonObject json);

QJsonObject DocumentToJson(Document* doc);
Document* JsonToDocument(QJsonObject json, QString name, Project* parent);

QJsonObject DocumentEntryToJson(DocumentEntry* entry);
void parseDocumentEntry(QJsonObject json, Document* document);

QJsonObject SchematicsSceneChildToJson(gui::SchematicsSceneChild* ssc);

namespace json {

// json -> *
q2d::metamodel::ConfigBitGroupDescriptor* toConfigBitGroupDescriptor(QJsonObject json);

// * -> json

} // namespace json
} // namespace q2d

#endif // JSONHELPERS_H
