#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include <QObject>
#include <QString>

namespace q2d {

class DocumentEntry;

namespace model {

// forward declaration
class Model;

// TODO documentation
class ModelElement : public QObject {
    Q_OBJECT
private:
    DocumentEntry* m_relatedEntry;
public:
    ModelElement(Model* parent, DocumentEntry* relatedEntry = nullptr);

    DocumentEntry* relatedEntry() const;
    void setRelatedEntry(q2d::DocumentEntry* relatedEntry);

    Model* model() const;
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
