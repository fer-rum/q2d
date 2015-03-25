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
class Port;

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

    virtual QStringList inputVariables()     const {
        return QStringList();
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

    /**
     * @brief id is an abbreviation for calling relatedEntry()->id()
     * @return
     */
    QString id() const {
       return m_relatedEntry->id();
    }
    /**
     * @brief toString offers a string representation of the model element.
     * This might be used for example in tooltips or for debugging.
     * @return
     */
    virtual QString toString()              const {
        return m_relatedEntry->id();
    }

signals:
    void signal_changed();
};

class InterfacingME
        : public ModelElement {
    Q_OBJECT
private:

protected:

    QList<Port*> m_ports;

    InterfacingME(DocumentEntry* relatedEntry)
        : ModelElement(relatedEntry){
        m_ports = QList<Port*>();
    }

public:
    void addPort(Port* port){
        Q_CHECK_PTR(port);
        m_ports.append(port);
    }
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
