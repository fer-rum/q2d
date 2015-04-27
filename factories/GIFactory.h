#ifndef COMPONENTGIFACTORY_H
#define COMPONENTGIFACTORY_H


#include "../metamodel/PortDescriptor.h"

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

    /**
     * @brief The PortEntry class is a helper class for component and module interface creation.
     * It provides the operator< for sorting.
     */
    class PortEntry {
    private:
        metamodel::PortDescriptor* m_descriptor;
        QGraphicsTextItem* m_textGraphics;
    public:
        PortEntry(metamodel::PortDescriptor* descriptor, QGraphicsItemGroup* parent);
        metamodel::PortDescriptor* descriptor()const { return m_descriptor; }
        QGraphicsTextItem* textGraphics(){ return m_textGraphics; }


        friend inline bool operator<(const GIFactory::PortEntry& left, const GIFactory::PortEntry& right){
            const QString textLeft = left.descriptor()->text();
            const QString textRight = right.descriptor()->text();

            return QString::compare(textLeft, textRight);
        }

    };

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
