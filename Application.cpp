#include "Application.h"

#include "logging/ConsoleLogger.h"
#include "logging/LogManager.h"
#include "logging/LogLevel.h"

#include "Document.h"

#include <QDir>
#include <QObject>
#include <QString>
#include <QtSvg/QGraphicsSvgItem>


using namespace q2d;
using namespace q2d::constants;

Application::Application(int &argc, char** argv[])
    : QApplication(argc, *argv), m_context(new ApplicationContext(this)), m_quantorInterface() {

    this->setApplicationName("q2d");
    this->setOrganizationName("Fredo Erxleben");

    // Logging
    this->setupLogging();

    // register metatypes
    qRegisterMetaType<QGraphicsSvgItem*>();

    // load settings (implicitly done when creating QSettings)
    this->m_appSettings = new QSettings();
    this->checkSettings();

    m_logManager->logger("General")->log("Settings loaded", m_logManager->logLevel("INFO"));

    // Application -> Quantor
    connect(this, &Application::signal_quantorTriggered,
            &m_quantorInterface, &quantor::QuantorInterface::slot_solveProblem);

    // Quantor -> Application
    connect(&m_quantorInterface, &quantor::QuantorInterface::signal_hasSolution,
            this, &Application::signal_quantorSolutionAvailable);

}

Application::~Application() {
    delete m_context;
    delete m_appSettings;
}

std::shared_ptr<logging::ConsoleLogger>
Application::consoleLogger() const {
    return m_consoleLogger;
}

std::shared_ptr<logging::LogManager>
Application::logManager() const {
    return m_logManager;
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
Application::setupLogging() {
    m_logManager = std::shared_ptr<logging::LogManager>(new logging::LogManager(this));
    // TODO put the default log levels in an enum
    auto levelDebug = m_logManager->logLevel("DEBUG");
    m_logManager->logLevel("INFO");
    m_logManager->logLevel("ERROR");
    auto generalLogger = m_logManager->logger("General");

    m_consoleLogger = std::shared_ptr<logging::ConsoleLogger>(new logging::ConsoleLogger(this));
    m_consoleLogger->connect(generalLogger);

    // print an initial message to show it works
    generalLogger->log("General logger says hello.", levelDebug);
}

void
Application::checkSettings() {

    // TODO this should be customizable as well
    QString basePath = QDir::homePath() + "/q2d";

    // paths
    this->defaultSetting(KEY_DIR_COMPONENTS,    basePath + "/components");
    this->defaultSetting(KEY_DIR_PROJECTS,      basePath + "/projects");
    this->defaultSetting(KEY_DIR_LIBRARIES,     basePath + "/libraries");

    // TODO deprecated
    this->defaultSetting(KEY_FILE_PORT_IN,      basePath + "/icons/port_in.svg");
    this->defaultSetting(KEY_FILE_PORT_INOUT,   basePath + "/icons/port_inout.svg");
    this->defaultSetting(KEY_FILE_PORT_OUT,     basePath + "/icons/port_out.svg");
    this->defaultSetting(KEY_FILE_BIT_GROUP,    basePath + "/icons/bit_group.svg");
    this->defaultSetting(KEY_FILE_OPORT_IN,     basePath + "/icons/outside_port_in.svg");
    this->defaultSetting(KEY_FILE_OPORT_OUT,    basePath + "/icons/outside_port_out.svg");
}

QVariant
Application::getSetting(QString key) {
    return this->m_appSettings->value(key);
}


void
Application::slot_resetSettings() {
    m_appSettings->clear();
    this->checkSettings();
}

Application*
Application::instance() {
    return dynamic_cast<Application*>(QApplication::instance());
}
