#include "Application.h"

using namespace q2d;

Application::Application(int &argc, char **argv[]) : QApplication(argc, *argv) {
}

void
Application::initialize(){
    // TODO load settings
    // TODO load basic libraries

    this->mainWindow = new gui::MainWindow();
}

void
Application::run(){
    this->mainWindow->show();
}

