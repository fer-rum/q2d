#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include <QObject>
#include <QString>
#include <QStringList>

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

    virtual QStringList nodeVariables()     const {
        return QStringList();
    }
    virtual QStringList configVariables()   const {
        return QStringList();
    }
    virtual QStringList functions()         const {
        return QStringList();
    }
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
