#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <QtSvg/QtSvg>

/*
 * The component types are represented by the QStandardItemModel.
 * There are categories and types.
 * Categories may be nested.
 *
 *
 */


namespace q2d {

    /**
     * @brief The ComponentType class contains common elements of all components of a certain type.
     *
     * A component type is the abstraction of component instances that share the same functionality and behaviour.
     */
class ComponentType : public QStandardItem {
        // TODO signals and slots
private:
    /**
     * @brief symbol the circuit symbol used in the UI.
     */
    QGraphicsSvgItem* symbol;
    // TODO port positions
    // TODO parameters?
    // todo functionality?
public:
    ComponentType(QString name, QGraphicsSvgItem* symbol);
};

class ComponentCategory : public QStandardItem {
    // TODO signals and slots
    // TODO later: mouse-over descriptions
    // TODO later: translations for names?
public:
    ComponentCategory(QString name);
    ~ComponentCategory();

    void addSubCategory(ComponentCategory* toAdd);
    void addComponentType(ComponentType* toAdd);
};

class ComponentFactory {
private:
    QStandardItemModel componentHierarchy;

    // TODO overload
    void addCategory(QString name, ComponentCategory* parent);
    void addType(QString name, ComponentCategory* parent);

public:
    ComponentFactory();
    ~ComponentFactory();
};

} // namespace q2d

#endif // COMPONENTTYPE_H
