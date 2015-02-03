#include "Application.h"

#include <QDir>
#include <QtSvg/QGraphicsSvgItem>


using namespace q2d;
using namespace q2d::constants;

Application::Application(int &argc, char** argv[]) : QApplication(argc, *argv) {

    this->setApplicationName("q2d");
    this->setOrganizationName("Fredo Erxleben");

    // register metatypes
    qRegisterMetaType<QGraphicsSvgItem*>();

    // TODO load settings
    this->m_appSettings = new QSettings();
    this->checkSettings();

    m_context = new ApplicationContext(this);
    Q_CHECK_PTR(m_context);
}

Application::~Application() {
    delete m_context;
    delete m_appSettings;
}

ApplicationContext*
Application::getContext() {
    return m_context;
}

void
Application::defaultSetting(QString name, QVariant defaultValue) {
    if (!this->m_appSettings->value(name).isValid()) {
        this->m_appSettings->setValue(name, defaultValue);
    }
}

void
Application::checkSettings() {

    QString basePath = QDir::homePath() + "/q2d";

    // paths
    this->defaultSetting(KEY_COMPONENTS_DIR,    basePath + "/components");
    this->defaultSetting(KEY_PROJECTS_DIR,      basePath + "/projects");
    this->defaultSetting(KEY_PORT_IN_FILE,      basePath + "/components/port_in.svg");
    this->defaultSetting(KEY_PORT_INOUT_FILE,   basePath + "/components/port_inout.svg");
    this->defaultSetting(KEY_PORT_OUT_FILE,     basePath + "/components/port_out.svg");
}

QVariant
Application::getSetting(QString key) {
    return this->m_appSettings->value(key);
}

Application*
Application::instance() {
    return dynamic_cast<Application*>(QApplication::instance());
}
