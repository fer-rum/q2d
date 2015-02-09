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
    QStandardItemModel componentHierarchy;

    // FIXME deprecated functions, move to json namespace
    // and create proper calling
    QJsonObject entryToJson(QStandardItem* item);
    QJsonObject categoryEntryToJson(QStandardItem* item);
    QJsonObject typeEntryToJson(QStandardItem* item);

    void jsonToCategoryEntry(QJsonObject json, metamodel::Category* parent = nullptr);
    void jsonToTypeEntry(QJsonObject json, metamodel::Category* parent);
    void jsonToEntry(QJsonObject json, metamodel::Category* parent);

public:
    explicit ComponentFactory(ApplicationContext* parent = 0);

    QStandardItemModel* getComponentHierarchy();
    metamodel::Category* getCategoryForIndex(const QModelIndex &index);
    metamodel::ComponentDescriptor* getTypeForIndex(const QModelIndex &index);
    metamodel::ComponentDescriptor* getTypeForHierarchyName(QString hierarchyName);


    // TODO instantiations should no longer be added to the document automatically
    // TODO can instantiations be made independent of documents until they are added?
    DocumentEntry* instantiateComponent(Document* document, QString hierarchyName,
                                        QPointF scenePosition, QString id = "");
    DocumentEntry* instantiateComponent(Document* document,
                                        metamodel::ComponentDescriptor* type,
                                        QPointF scenePosition,
                                        QString id = "");
    QList<DocumentEntry*> instantiatePorts(Document* document,
                                           metamodel::ComponentDescriptor* type,
                                           DocumentEntry* parentComponent);
    DocumentEntry* instantiatePort(Document* document,
                                   DocumentEntry* parentComponent,
                                   QPointF position,
                                   model::enums::PortDirection direction,
                                   QString id);
    DocumentEntry* instantiateWire(Document* document,
                                   DocumentEntry* sender,
                                   DocumentEntry* receiver,
                                   QString id);
    QJsonDocument exportHierarchy();
    void importHierarchy(QJsonDocument source);


public slots:
    void slot_loadType(QString filePath, metamodel::Category* parent);
    metamodel::Category* slot_addCategory(QString name, metamodel::Category* parent);
    void slot_clearHierarchy();

};

} // namespace q2d

#endif // COMPONENTFACTORY_H
