#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include <QMap>

/**
 * @brief The MapModel class
 * @author mhcuervo
 *
 * COPYRIGHT NOTICE: this class was originally written by mhcuervo as posted on
 * http://stackoverflow.com/questions/23484511/how-to-display-a-simple-qmap-in-a-qtableview-in-qt
 * Changes were made due to refactoring and adaption to the concrete use case.
 */
namespace q2d {
namespace util {

class MapModel : public QAbstractTableModel {
    Q_OBJECT
private:
    const QMap<QString, bool>* m_map;
public:

    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit MapModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    inline void setMap(const QMap<QString, bool>* map) {
        m_map = map;
    }
};

}
}

#endif // MAPMODEL_H
