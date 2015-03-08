#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include "../DocumentEntry.h"

#include <QObject>
#include <QString>
#include <QStringList>

namespace q2d {
namespace model {

// forward declaration
class Model;

// TODO documentation
class ModelElement : public QObject {
    Q_OBJECT
private:
    DocumentEntry* m_relatedEntry;
public:
    ModelElement(DocumentEntry* relatedEntry);

    DocumentEntry* relatedEntry() const;
    void setRelatedEntry(q2d::DocumentEntry* relatedEntry);

    /**
     * @brief model is a shurtcut to querying the related document entry for the model.
     * @return
     */
    inline Model* model() const {
        return m_relatedEntry->model();
    }

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
