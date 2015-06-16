#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Enumerations.h"

#include <QFile>
#include <QJsonDocument>
#include <QObject>
#include <QStandardItemModel>

namespace q2d {

// forward declaration
class ApplicationContext;
class Document;
class DocumentEntry;

namespace metamodel {
class Category;
class HierarchyElement;
class ComponentDescriptor;
}

namespace model {
class Component;
class Model;
}

class ComponentFactory : public QObject {
    Q_OBJECT

private:
    QStandardItemModel m_componentHierarchy;

    // TODO: does not belong here
    void jsonToCategoryEntry(QJsonObject json, metamodel::Category* parent = nullptr);
    void jsonToTypeEntry(QJsonObject json, metamodel::Category* parent);
    void jsonToEntry(QJsonObject json, metamodel::Category* parent);

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* componentHierarchy();
    metamodel::Category* categoryForIndex(const QModelIndex &index);
    metamodel::ComponentDescriptor* componentDescriptor(const QModelIndex &index);
    metamodel::ComponentDescriptor* componentDescriptor(const QString hierarchyName);

    void importHierarchy(QJsonDocument source);


public slots:
    void slot_loadType(QString filePath, metamodel::Category* parent);
    metamodel::Category* slot_addCategory(QString name, metamodel::Category* parent);
    void slot_clearHierarchy();
    void slot_saveHierarchy(QString filePath);
    void slot_loadHierarchy(QString filePath);

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
