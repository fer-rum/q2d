#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

class Element :
        public QObject,
        public QStandardItem {
    Q_OBJECT
public:
    explicit Element(QString name, Element* parent = nullptr)
        : QObject(parent), QStandardItem(name){}

    virtual Element* parent() const {
        return static_cast<Element*>(QObject::parent());
    }

    virtual void setParent(Element* parent) {
        QObject::setParent(parent);
    }

    virtual int type() const override = 0;
};

} // namespace metamodel
} // namespace q2d


#endif // ELEMENT_H
