#ifndef DOCUMENTENTRY_H
#define DOCUMENTENTRY_H

#include <QGraphicsItem>
#include <QString>

namespace q2d {

// forward declaration
namespace model {
    class ModelElement;
}

/**
 * @brief The DocumentEntry class keeps a mapping between model and schematic elements
 * as well as the unique ids associated with them.
 *
 * DocumentEntry may have parents, to maintain any potential hierarchical relations.
 */
class DocumentEntry {
private:
    QString                 m_id;
    model::ModelElement*    m_modelElement;
    QGraphicsItem*          m_schematicElement;
    DocumentEntry*          m_parent;
public:
    DocumentEntry(QString id, model::ModelElement* modelElement,
                  QGraphicsItem* schematicElement, DocumentEntry* parent = nullptr);
    QString id() const;
    model::ModelElement* modelElement() const;
    QGraphicsItem* schematicElement() const;
    DocumentEntry* parent() const;
};

} // namespace q2d
#endif // DOCUMENTENTRY_H
