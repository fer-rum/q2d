#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "Application.h"
#include "ComponentType.h"
#include "MainWindow.h"
#include "Project.h"

#include <QObject>

namespace q2d {

    // forward declaration
    class Application;
    class Project;
    class ComponentFactory;

    namespace gui {
        class MainWindow;
    }


// TODO documentation
class ApplicationContext : public QObject {
    Q_OBJECT
private:
    Project* currentProject;
    gui::MainWindow* mainWindow;
    ComponentFactory componentFactory;

     void createProject(QString name);

public:
    explicit ApplicationContext(Application* parent);

     Project* getCurrentProject();
     gui::MainWindow* getMainWindow();
     ComponentFactory* getComponentFactory();

     void setupSignalsAndSlots();

signals:
     void signal_projectNameChanged(QString newName);
     void signal_canAddDocuments(bool newState);
     void signal_createDocument();
     void signal_documentModelChanged(QStandardItemModel* model);
     void signal_componentModelChanged(QStandardItemModel* model);

public slots:
    void slot_newDocument();
    void slot_newProject();
    void slot_projectNameChanged(QString newName);
};

}
#endif // APPLICATIONCONTEXT_H
