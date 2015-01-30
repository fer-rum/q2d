#ifndef JSONHELPERS_H
#define JSONHELPERS_H

#include "Document.h"
#include "DocumentEntry.h"

#include <QJsonObject>
#include <QPointF>

namespace q2d {

void WriteJsonFile(QString path, QJsonDocument doc);

QJsonObject PointToJson(QPointF point);
QPointF JsonToPoint(QJsonObject json);

QJsonObject DocumentToJson(Document* doc);
Document* JsonToDocument(QJsonObject json, QString name, Project* parent);

QJsonObject DocumentEntryToJson(DocumentEntry* entry);
void parseDocumentEntry(QJsonObject json, Document* document);

QJsonObject SchematicsSceneChildToJson(gui::SchematicsSceneChild* ssc);


} // namespace q2d

#endif // JSONHELPERS_H
