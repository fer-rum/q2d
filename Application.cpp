#include "Application.h"

#include <QDir>

// TODO constants for setting names

using namespace q2d;

Application::Application(int &argc, char **argv[]) : QApplication(argc, *argv) {

    this->setApplicationName("q2d");
    this->setOrganizationName("Fredo Erxleben");

    // TODO load settings
    this->applicationSettings = new QSettings();
    this->checkSettings();

    this->context = new ApplicationContext(this);
    Q_CHECK_PTR(this->context);
}

Application::~Application() {
    delete this->context;
    delete this->applicationSettings;
}

ApplicationContext*
Application::getContext(){
    return this->context;
}


void
Application::defaultSetting(QString name, QVariant defaultValue){
    if(!this->applicationSettings->value(name).isValid()){
        this->applicationSettings->setValue(name, defaultValue);
    }
}

void
Application::checkSettings(){

    // paths
    this->defaultSetting(constants::KEY_COMPONENTS_DIR, QDir::homePath() + "/q2d/components");
    this->defaultSetting(constants::KEY_PROJECTS_DIR, QDir::homePath() + "/q2d/projects");
}

QVariant
Application::getSetting(QString key){
    return this->applicationSettings->value(key);
}
