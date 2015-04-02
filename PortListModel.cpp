#include "factories/ToolTipFactory.h"
#include "model/Port.h"
#include "PortListModel.h"

using namespace q2d::util;

PortListModel::PortListModel(QObject* parent) :
    QAbstractListModel(parent) {}

PortListModel::~PortListModel() {
    delete m_list;
}

int
PortListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_list->count();
}

QVariant
PortListModel::data(const QModelIndex &index, int role) const {

    if (index.row() < 0 ||
            index.row() >= m_list->count() ||
            role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole :
        return m_list->value(index.row())->relatedEntry()->fullId();
    case TooltipRole:
        return factories::ToolTipFactory::toHtmlTable(m_list->value(index.row())->propertyMap());
    default:
        return QVariant();
    }
}
