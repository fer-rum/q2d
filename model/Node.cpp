
#include "../DocumentEntry.h"
#include "Node.h"
#include "Component.h"

using namespace q2d::model;

Node::Node(DocumentEntry* relatedEntry)
    : ModelElement(relatedEntry) {
    m_driver = nullptr;
    m_drivenElements = QList<ModelElement*>();
}

void
Node::addDriver(ModelElement* driver) {
    Q_CHECK_PTR(driver);
    Q_ASSERT(m_driver == nullptr);
    // no driver must be set yet
    // multiple drivers per node are not allowed for now.

    m_driver = driver;
    emit this->signal_changed();
}

void
Node::addDrivenElement(ModelElement* drivenElement) {
    Q_CHECK_PTR(drivenElement);
    m_drivenElements.append(drivenElement);
    emit this->signal_changed();
}

QString
Node::toString() const {
    QString text = ModelElement::toString();
    ModelElement* driver = this->driver();
    text += "\nDriver: ";
    if(driver != nullptr){
        text += driver->relatedEntry()->id();
    } else {
        text += "(None)";
    }

    for(ModelElement* current : this->drivenElements()){
        text += "\n-> " + current->relatedEntry()->id();
    }

    return text;
}
