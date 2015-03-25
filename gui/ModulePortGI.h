#ifndef MODULEPORTGI_H
#define MODULEPORTGI_H

#include "../Enumerations.h"
#include "SchematicElement.h"

#include <QPointF>
#include <QVariant>

namespace q2d {
class DocumentEntry;

namespace gui {
class PortGraphicsItem;

class ModulePortGI : public ParentSchematicElement {

private:

    model::enums::PortDirection m_moduleDirection;

protected :
    /**
     * @brief ModulePortGI::specificType is the PortDirection as viewed from outside the module.
     * Therefore, the internal value is to be reversed.
     * So an input port will return <i>in</i> and an output port will return <i>out</i>.
     * @return The (inverted) PortDirection as String
     */
    virtual QString specificType() override;

public:
    ModulePortGI(QPointF position, DocumentEntry* relatedEntry,
                     model::enums::PortDirection direction);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

} // namespace gui
} // namespace q2d

#endif // MODULEPORTGI_H
