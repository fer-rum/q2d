#include "JsonHelpers.h"

#include "Constants.h"

#include <QJsonValue>

using namespace q2d::constants;

QJsonObject
q2d::PointToJson(QPointF point){
    Q_ASSERT(!point.isNull());

    QJsonObject result = QJsonObject();

    result.insert(JSON_POSITION_X, QJsonValue(point.x()));
    result.insert(JSON_POSITION_Y, QJsonValue(point.y()));

    return result;
}
