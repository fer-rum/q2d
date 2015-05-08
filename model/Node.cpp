
#include "../DocumentEntry.h"
#include "../factories/ToolTipFactory.h"
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
    if(m_driver != nullptr){
    // no driver must be set yet
    // multiple drivers per node are not allowed for now.
        // TODO emit error message
        return;
    }
    m_driver = driver;
    emit this->signal_changed();
}

void
Node::addDrivenElement(ModelElement* drivenElement) {
    Q_CHECK_PTR(drivenElement);
    m_drivenElements.append(drivenElement);
    emit this->signal_changed();
}

QMap<QString, QString>
Node::propertyMap() const {
    return factories::ToolTipFactory::propertyMap(this);
}
