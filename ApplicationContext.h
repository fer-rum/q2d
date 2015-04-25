#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include <QDir>
#include <QObject>
#include <QStandardItemModel>

namespace q2d {

// forward declaration
class Application;

namespace gui {
class MainWindow;
}

namespace metamodel {
class Category;
}

namespace model {
class Component;
}
class ComponentFactory;
class Project;
class Document;


// TODO documentation
// TODO close projects
class ApplicationContext : public QObject {
    Q_OBJECT
private:
    Application* m_application;
    Project* m_currentProject = nullptr;
    gui::MainWindow* m_mainWindow;
    ComponentFactory* m_componentFactory;

    // TODO
    // utility functions to delegate to,
    // that do all the little works
    void createProject(QString name);
    void/*?*/ unloadProject(/*…*/);
    void/*?*/ loadProject(/*…*/);


public:
    explicit ApplicationContext(Application* parent);
    virtual ~ApplicationContext();

    bool hasCurrentProject(); // TODO const
    Project* getCurrentProject(); // TODO const
    gui::MainWindow* getMainWindow(); // TODO const
    ComponentFactory* componentFactory(); // TODO const

    void setupSignalsAndSlots();

signals:
    void signal_projectNameChanged(QString newName);
    void signal_canSaveProjects(bool newState);
    void signal_canAddDocuments(bool newState);
    void signal_createDocument(QString name);
    void signal_documentModelChanged(QStandardItemModel* model);
    void signal_componentModelChanged(QStandardItemModel* model);
    void signal_saveProject();
    void signal_triggerQuantor(Document* document, QStringList targetFunctions);

    // forwards to component factory
    void signal_createComponentCategory(QString name, metamodel::Category* parent);
    void signal_clearComponentTypes();
    void signal_saveLibraryRequested(QString filePath);
    void signal_loadLibraryRequested(QString filePath);

    // forwarding signal to MainWindow
    void signal_showDocument(Document* document);
    void signal_quantorSolutionAvailable(QString, const QMap<QString, bool>*);
    void signal_error(QString title, QString text);

public slots:
    void slot_newDocument(QString name);
    void slot_newProject(QString name);
    void slot_projectNameChanged(QString newName);
    void slot_loadProject(QString projectDirPath);
    void slot_unloadProject();
};

}
#endif // APPLICATIONCONTEXT_H
