#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QFile>
#include <QObject>
#include <QStandardItemModel>

namespace q2d {

    // forward declaration
    class ApplicationContext;
    class ComponentCategory;
    class ComponentType;

class ComponentFactory : public QObject {
    Q_OBJECT

private:
    QStandardItemModel componentHierarchy;

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* getComponentHierarchy();
    ComponentCategory* getCategoryForIndex(const QModelIndex &index);
    ComponentType* getTypeForIndex(const QModelIndex &index);

public slots:
    void slot_loadType(QString fileName, ComponentCategory* parent);
    void slot_addCategory(QString name, ComponentCategory* parent);

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
