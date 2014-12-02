#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationContext.h"
#include "MainWindow.h"

#include <QApplication>
#include <QSettings>

namespace q2d {

    // forward declaration
    namespace gui {
        class MainWindow;
    }

class Application : public QApplication {
    Q_OBJECT
private:
    QSettings applicationSettings;
    ApplicationContext context;
    q2d::gui::MainWindow* mainWindow;

public:
    explicit Application(int &argc, char **argv[]);
    void initialize();
    void run();

signals:

public slots:

};

} // namespace q2d

#endif // APPLICATION_H
