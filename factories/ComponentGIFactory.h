#ifndef COMPONENTGIFACTORY_H
#define COMPONENTGIFACTORY_H

#include <QGraphicsItem>
#include <QPointF>

namespace q2d {
class DocumentEntry;

namespace metamodel {
class ComponentDescriptor;
}

namespace factories {

class ComponentGIFactory {
private:
    /**
     * @brief TEXT_PADDING the amount of whitespace around any text in pixels.
     */
    static unsigned int TEXT_PADDING;

public:
    ComponentGIFactory();

    /**
 * @brief createComponentGI generates a new QGraphicsItem for a given component type.
 * Note that this function has side effects: it changes the position of the port descriptors to match the generated graphics.
 * @param type
 * @return
 */
static QGraphicsItem* createComponentGI(metamodel::ComponentDescriptor* type);

};

} // namespace factories
} // namespace q2d

#endif // COMPONENTGIFACTORY_H
