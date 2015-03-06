#ifndef APPLICATION_H
#define APPLICATION_H

#include "interfaces/Quantor.h"
#include "ApplicationContext.h"
#include "Constants.h"

#include <QApplication>
#include <QSettings>

namespace q2d {

class Application : public QApplication {
    Q_OBJECT
private:
    QSettings* m_appSettings;
    ApplicationContext* m_context;
    quantor::QuantorInterface m_quantorInterface;

    void defaultSetting(QString name, QVariant defaultValue);
    void checkSettings();

public:

    explicit Application(int &argc, char** argv[]);
    virtual ~Application();

    ApplicationContext* getContext();
    QVariant getSetting(QString key);

    static Application* instance();
signals:

    // --- forwarded signals ---
    // ApplicationContext -> Quantor
    void signal_quantorTriggered(Document* document, QString targetFunction);

    // Quantor -> ApplicationContext -> MainWindow
    void signal_quantorSolutionAvailable(QString, const QMap<QString, bool>*);

public slots:
    void slot_resetSettings();

};

} // namespace q2d

#endif // APPLICATION_H
