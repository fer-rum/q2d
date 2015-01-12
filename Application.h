#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationContext.h"
#include "Constants.h"

#include <QApplication>
#include <QSettings>

namespace q2d {

class Application : public QApplication {
    Q_OBJECT
private:
    QSettings* applicationSettings;
    ApplicationContext* context;

    void defaultSetting(QString name, QVariant defaultValue);
    void checkSettings();

public:

    explicit Application(int &argc, char **argv[]);
    virtual ~Application();

    ApplicationContext* getContext();
    QVariant getSetting(QString key);

    static Application* instance();
signals:

public slots:
};

} // namespace q2d

#endif // APPLICATION_H
