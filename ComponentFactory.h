#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "model/PortDirection.h"

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
class ComponentCategory;
class ComponentDescriptor;
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

    metamodel::ComponentType* createTypeFromJson(const QJsonDocument jsonSource,
            const QString basePath,
            metamodel::ComponentCategory* parent);

    QJsonObject entryToJson(QStandardItem* item);
    QJsonObject categoryEntryToJson(QStandardItem* item);
    QJsonObject typeEntryToJson(QStandardItem* item);

    void jsonToCategoryEntry(QJsonObject json, metamodel::ComponentCategory* parent = nullptr);
    void jsonToTypeEntry(QJsonObject json, metamodel::ComponentCategory* parent);
    void jsonToEntry(QJsonObject json, metamodel::ComponentCategory* parent);

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* getComponentHierarchy();
    metamodel::ComponentCategory* getCategoryForIndex(const QModelIndex &index);
    metamodel::ComponentType* getTypeForIndex(const QModelIndex &index);
    metamodel::ComponentType* getTypeForHierarchyName(QString hierarchyName);

    DocumentEntry* instantiateComponent(Document* document, QString hierarchyName,
                                        QPointF scenePosition, QString id = "");
    DocumentEntry* instantiateComponent(Document* document,
                                        metamodel::ComponentType* type,
                                        QPointF scenePosition,
                                        QString id = "");
    QList<DocumentEntry*> instantiatePorts(Document* document,
                                           metamodel::ComponentType* type,
                                           DocumentEntry* parentComponent);
    DocumentEntry* instantiatePort(Document* document,
                                   DocumentEntry* parentComponent,
                                   QPointF position,
                                   model::PortDirection direction,
                                   QString id);
    DocumentEntry* instantiateWire(Document* document,
                                   DocumentEntry* sender,
                                   DocumentEntry* receiver,
                                   QString id);
    QJsonDocument exportHierarchy();
    void importHierarchy(QJsonDocument source);


public slots:
    void slot_loadType(QString fileName, metamodel::ComponentCategory* parent);
    metamodel::ComponentCategory* slot_addCategory(QString name, metamodel::ComponentCategory* parent);
    void slot_clearHierarchy();

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
