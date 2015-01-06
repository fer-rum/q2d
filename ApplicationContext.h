#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include <QObject>
#include <QStandardItemModel>

namespace q2d {

    // forward declaration
    class Application;

    namespace gui {
        class MainWindow;
    }

    class ComponentFactory;
    class Project;


// TODO documentation
    // TODO close projects
class ApplicationContext : public QObject {
    Q_OBJECT
private:
    Project* currentProject = nullptr;
    gui::MainWindow* mainWindow;
    ComponentFactory* componentFactory;

public:
    explicit ApplicationContext(Application* parent);
    virtual ~ApplicationContext();

     Project* getCurrentProject();
     gui::MainWindow* getMainWindow();
     ComponentFactory* getComponentFactory();

     void setupSignalsAndSlots();

signals:
     void signal_projectNameChanged(QString newName);
     void signal_canAddDocuments(bool newState);
     void signal_createDocument(QString name);
     void signal_documentModelChanged(QStandardItemModel* model);
     void signal_componentModelChanged(QStandardItemModel* model);

public slots:
    void slot_newDocument(QString name);
    void slot_newProject(QString name);
    void slot_projectNameChanged(QString newName);
};

}
#endif // APPLICATIONCONTEXT_H
