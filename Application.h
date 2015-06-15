#ifndef APPLICATION_H
#define APPLICATION_H

#include "interfaces/Quantor.h"
#include "ApplicationContext.h"
#include "Constants.h"

#include "logging/ConsoleLogger.h"
#include "logging/LogManager.h"

#include <QApplication>
#include <QSettings>

#include <memory>

namespace q2d {

class Application
        : public QApplication {
    Q_OBJECT
private:
    QSettings* m_appSettings;
    ApplicationContext* m_context;
    quantor::QuantorInterface m_quantorInterface;

    logging::LogManager* m_logManager;
    logging::ConsoleLogger* m_consoleLogger;

    void defaultSetting(QString name, QVariant defaultValue);
    void checkSettings();
    void setupLogging();

    /**
     * @brief m_logger the logger used by everything related to the application itself.
     */
    logging::Logger* m_logger;

public:

    explicit Application(int &argc, char** argv[]);
    virtual ~Application();

    ApplicationContext* getContext();
    QVariant getSetting(QString key);

    logging::ConsoleLogger* consoleLogger() const;
    logging::LogManager* logManager() const;

    static Application* instance();
signals:

    // --- forwarded signals ---
    // ApplicationContext -> Quantor
    void signal_quantorTriggered(Document* document, QStringList targetFunctions);

    // Quantor -> ApplicationContext -> MainWindow
    void signal_quantorSolutionAvailable(QString, const QMap<QString, bool>*);

public slots:
    void slot_resetSettings();

};

} // namespace q2d

#endif // APPLICATION_H
