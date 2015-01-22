#include "Application.h"

#include <QDir>
#include <QtSvg/QGraphicsSvgItem>

// TODO constants for setting names

using namespace q2d;
using namespace q2d::constants;

Application::Application(int &argc, char **argv[]) : QApplication(argc, *argv) {

    this->setApplicationName("q2d");
    this->setOrganizationName("Fredo Erxleben");

    // register metatypes
    qRegisterMetaType<QGraphicsSvgItem*>();

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

    QString basePath = QDir::homePath() + "/q2d";

    // paths
    this->defaultSetting(KEY_COMPONENTS_DIR,    basePath + "/components");
    this->defaultSetting(KEY_PROJECTS_DIR,      basePath + "/projects");
    this->defaultSetting(KEY_PORT_IN_FILE,      basePath + "/components/port_in.svg");
    this->defaultSetting(KEY_PORT_INOUT_FILE,   basePath + "/components/port_inout.svg");
    this->defaultSetting(KEY_PORT_OUT_FILE,     basePath + "/components/port_out.svg");
}

QVariant
Application::getSetting(QString key){
    return this->applicationSettings->value(key);
}

Application*
Application::instance(){
    return dynamic_cast<Application*>(QApplication::instance());
}
