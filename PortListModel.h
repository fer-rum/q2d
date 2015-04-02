#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>

namespace q2d {

namespace model {
class ComponentPort;
}

namespace util {

class PortListModel
        : public QAbstractListModel {
    Q_OBJECT
private:
    const QList<model::ComponentPort*>* m_list;
public:

    explicit PortListModel(QObject* parent = 0);
    virtual ~PortListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    inline void setList(const QList<model::ComponentPort*>* list) {
        m_list = list;
    }
};

} // namespace util
} // namespace q2d

#endif // LISTMODEL_H
