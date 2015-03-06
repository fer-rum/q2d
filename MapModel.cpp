#include "MapModel.h"

using namespace q2d::util;

MapModel::MapModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_map = nullptr;
}

int MapModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    if (m_map)
        return m_map->count();
    return 0;
}

int MapModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant MapModel::data(const QModelIndex& index, int role) const
{
    if (m_map == nullptr)
        return QVariant();
    if (index.row() < 0 ||
        index.row() >= m_map->count() ||
        role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0)
        return m_map->keys().at(index.row());
    if (index.column() == 1)
        return m_map->values().at(index.row());
    return QVariant();
}
