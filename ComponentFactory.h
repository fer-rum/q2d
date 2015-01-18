#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QFile>
#include <QJsonDocument>
#include <QObject>
#include <QStandardItemModel>

namespace q2d {

    // forward declaration
    class ApplicationContext;

    namespace metamodel {
    class ComponentCategory;
    class ComponentType;
    }

    namespace model {
    class Component;
    class Model;
    }

class ComponentFactory : public QObject {
    Q_OBJECT

private:
    QStandardItemModel componentHierarchy;

    metamodel::ComponentType* createTypeFronJson(const QJsonDocument jsonSource,
            const QString basePath,
            metamodel::ComponentCategory* parent);

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* getComponentHierarchy();
    metamodel::ComponentCategory* getCategoryForIndex(const QModelIndex &index);
    metamodel::ComponentType* getTypeForIndex(const QModelIndex &index);
    metamodel::ComponentType* getTypeForHierarchyName(QString hierarchyName);
    model::Component* instantiateComponent(metamodel::ComponentType* type, model::Model* model);

public slots:
    void slot_loadType(QString fileName, metamodel::ComponentCategory* parent);
    void slot_addCategory(QString name, metamodel::ComponentCategory* parent);

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
