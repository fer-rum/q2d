#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <QObject>
#include <QtSvg/QtSvg>

/*
 * The component types are represented by the QStandardItemModel.
 * There are categories and types.
 * Categories may be nested.
 */

namespace q2d {

    // forward declaration
    class ComponentType;


/**
 * @brief The ComponentDescriptorRole enum lists all roles, that can be fulfilled in describing an ComponentType.
 */
enum ComponentDescriptorRole {
    CIRCUIT_SYMBOL = Qt::UserRole + 2000,
    PORT_INFORMATION
    // TODO custom parameters
    // TODO boolean function
};

class ComponentDescriptor :
        public QObject,
        public QStandardItem {
    Q_OBJECT
public:
    ComponentDescriptor(QString name, QObject* parent = 0);
};

class ComponentCategory : public ComponentDescriptor {
    // TODO signals and slots
    // TODO later: mouse-over descriptions
    // TODO later: translations for names?
public:
    ComponentCategory(QString name, QObject* parent = 0);
    ~ComponentCategory();

    void addComponentType (ComponentType *toAdd);
    void addSubCategory (ComponentCategory *toAdd);
};

    /**
     * @brief The ComponentType class contains common elements of all components of a certain type.
     *
     * A component type is the abstraction of component instances that share the same functionality and behaviour.
     */
class ComponentType : public ComponentDescriptor {
        // TODO signals and slots
private:

public:
    ComponentType(QString name, QObject* parent = 0);
    void setCircuitSymbol(QGraphicsSvgItem* symbol);
    // TODO setPortInformation
};

class ComponentFactory {
private:
    QStandardItemModel componentHierarchy;

public:
    ComponentFactory();
    ~ComponentFactory();

    // TODO overload
    void addCategory(QString name, ComponentCategory* parent);
    void addType(QString name, ComponentCategory* parent);

    QStandardItemModel* getComponentHierarchy();
    ComponentCategory* getCategoryForIndex(const QModelIndex &index);
    ComponentType* getTypeForIndex(const QModelIndex &index);
};

} // namespace q2d

#endif // COMPONENTTYPE_H
