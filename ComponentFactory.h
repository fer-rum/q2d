#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QFile>
#include <QJsonDocument>
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

    ComponentType* createTypeFronJson(const QJsonDocument jsonSource,
            const QString basePath,
            ComponentCategory* parent);

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* getComponentHierarchy();
    ComponentCategory* getCategoryForIndex(const QModelIndex &index);
    ComponentType* getTypeForIndex(const QModelIndex &index);
    ComponentType* getTypeForHierarchyName(QString hierarchyName);

public slots:
    void slot_loadType(QString fileName, ComponentCategory* parent);
    void slot_addCategory(QString name, ComponentCategory* parent);

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
