#ifndef JSONHELPERS_H
#define JSONHELPERS_H

#include <QJsonObject>
#include <QPointF>

namespace q2d {

QJsonObject PointToJson(QPointF point);
// TODO JsonToPoint(QJsonObject json);
// TODO writeJsonFile(QString path, QJsonDocument doc);

} // namespace q2d

#endif // JSONHELPERS_H
