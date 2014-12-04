#include "Application.h"

#include <QMessageBox>

using namespace q2d;

Application::Application(int &argc, char **argv[]) : QApplication(argc, *argv) {
    // TODO load settings
    this->applicationSettings = new QSettings(this);

    this->context = new ApplicationContext(this);
    Q_CHECK_PTR(this->context);

    this->context->setupSignalsAndSlots();
}

Application::~Application() {
    delete this->context;
    delete this->applicationSettings;
}

ApplicationContext*
Application::getContext(){
    return this->context;
}
