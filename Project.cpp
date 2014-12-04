#include "Project.h"

using namespace q2d;

Project::Project(QString name, ApplicationContext* parent) : QObject(parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    this->name = name;
}

void
Project::setupSignalsAndSlots(){
    connect(this, SIGNAL(signal_nameChanged(QString)), this->parent(), SLOT(slot_projectNameChanged(QString)));
}
