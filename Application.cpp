#include "Application.h"

#include <QMessageBox>

using namespace q2d;

Application::Application(int &argc, char **argv[]) : QApplication(argc, *argv) {
    this->initialize();
}

Application::~Application() {
    delete this->mainWindow;
    delete this->context;
    delete this->applicationSettings;
}

void
Application::initialize(){
    // TODO load settings
    this->applicationSettings = new QSettings(this);
    // TODO load basic libraries
    this->mainWindow = new gui::MainWindow();
    this->context = new ApplicationContext(this);


    Q_CHECK_PTR(this->context);
    Q_CHECK_PTR(this->mainWindow);

    this->mainWindow->setupSignalsAndSlots();
    this->context->setupSignalsAndSlots();

    // show the main window
    this->mainWindow->show();
}

ApplicationContext*
Application::getContext(){
    return this->context;
}

q2d::gui::MainWindow*
Application::getMainWindow(){
    // TODO constness?
    return this->mainWindow;
}
