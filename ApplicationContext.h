#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "Application.h"
#include "MainWindow.h"
#include "Project.h"

#include <QObject>

namespace q2d {

    // forward declaration
    class Application;
    class Project;

    namespace gui {
        class MainWindow;
    }


// TODO documentation
class ApplicationContext : public QObject {
    Q_OBJECT
private:
    Project* currentProject;
    gui::MainWindow* mainWindow;

     void createProject(QString name);

public:
    explicit ApplicationContext(Application* parent);

     void setupSignalsAndSlots();

signals:
     void signal_projectNameChanged(QString newName);

public slots:
    void slot_newProject();
    void slot_projectNameChanged(QString newName);
};

}
#endif // APPLICATIONCONTEXT_H
