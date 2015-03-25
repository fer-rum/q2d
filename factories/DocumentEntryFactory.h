#ifndef DOCUMENTENTRYFACTORY_H
#define DOCUMENTENTRYFACTORY_H

#include <QMap>
#include <QList>
#include <QPointF>

namespace q2d {
class Document;
class DocumentEntry;

namespace metamodel {
class ComponentDescriptor;
} // namespace metamodel

namespace model{
namespace enums{
enum class PortDirection;
} // namespace enums
} // namespace model


namespace factories {

class DocumentEntryFactory {

private:

    // TODO instance counts should probably be document-dependent
    static QMap<QString, unsigned int> instanceCount;
    /**
     * @brief countInstance is an accessor to the component instance count.
     * It increments the actual count for the type and returns the new count.
     * @param typeName
     * @return
     */
    static unsigned int countInstance(QString typeName);

    // --- ID generators ---
    static QString generateComponentId(q2d::metamodel::ComponentDescriptor* type);

    // --- instantiation helpers ---

    /**
     * @brief instantiatePorts instantiates all ports
     * as described in the provided component descriptor.
     * @param document
     * @param type
     * @param parentComponent
     * @return A list with containing a DocumentEntry for each instantiated port
     */
    static QList<DocumentEntry*> instantiatePorts(
            Document* document,
            metamodel::ComponentDescriptor* type,
            DocumentEntry* parentComponent);

    /**
     * @brief instantiateModulePort is a helper method. It does not do everything needed, but a subset,
     * so do not call it on its own. Use instantiateInputPort() or instantiateOutputPort() respectively.
     * @param document
     * @param position
     * @param id
     * @param direction
     * @return
     */
    static DocumentEntry* instantiateModuleInterface(
            Document* document,
            QPointF position,
            model::enums::PortDirection direction,
            QString id);

public:

    /**
     * @brief ComponentFactory::instentiatePort
     * Instantiates a single Port and adds it to the document as DocumentEntry.
     * The schematic item of the parent entry is required to provide
     * <code> void signal_posChanged() </code>
     * A tooltip for the new ports schematic item will be set, containing its ID.
     * @param parentComponent
     * @param position
     * @param direction
     * @param id
     * @return
     */
    static DocumentEntry* instantiatePort(
            Document* document,
            DocumentEntry* parentComponent,
            QPointF position,
            model::enums::PortDirection direction,
            QString id);

    /**
     * @brief instantiateComponent
     * The instantiated Component will be wrapped into a DocumentEntry
     * and added to the document.
     * @param document
     * @param type
     * @param scenePosition
     * @param id
     * @return
     */
    static DocumentEntry* instantiateComponent(Document* document,
            metamodel::ComponentDescriptor* type,
            QPointF scenePosition,
            QString id = "",
            bool autoInstancePorts = true);

    static DocumentEntry* instantiateWire(
            Document* document,
            DocumentEntry* sender,
            DocumentEntry* receiver,
            QString id);

    static DocumentEntry* instantiateInputPort(
            Document* document,
            QPointF position,
            QString id);

    static DocumentEntry* instantiateOutputPort(
            Document* document,
            QPointF position,
            QString id);
};

} // namespcae factories
} // namespace q2d

#endif // DOCUMENTENTRYFACTORY_H
