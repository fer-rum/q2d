#ifndef COMPONENTGIFACTORY_H
#define COMPONENTGIFACTORY_H

#include "../Enumerations.h"
#include <QGraphicsItem>
#include <QPointF>

namespace q2d {
class DocumentEntry;

namespace metamodel {
class ComponentDescriptor;
}

namespace factories {

class GIFactory {
private:
    /**
     * @brief TEXT_PADDING the amount of whitespace around any text in pixels.
     */
    static unsigned int TEXT_PADDING;


public:
    GIFactory();

    /**
 * @brief createComponentGI generates a new QGraphicsItem for a given component type.
 * Note that this function has side effects: it changes the position of the port descriptors to match the generated graphics.
 * @param type
 * @return
 */
static QGraphicsItem* createComponentGI(metamodel::ComponentDescriptor* type);

/**
 * @brief createPortAdapterGI whichis used for the IN port direction.
 * @return
 */
static QAbstractGraphicsShapeItem* createPortAdapterGI();

/**
 * @brief createPortAdapteeGI which is used for the OUT port direction
 * @return
 */
static QAbstractGraphicsShapeItem* createPortAdapteeGI();
static QAbstractGraphicsShapeItem* createPortInvalidGI();

static QAbstractGraphicsShapeItem* createModulePortDecalIn();
static QAbstractGraphicsShapeItem* createModulePortDecalOut();

};

} // namespace factories
} // namespace q2d

#endif // COMPONENTGIFACTORY_H
