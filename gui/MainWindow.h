// TODO move all related files to gui folder, where it belongs

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include "metamodel/ComponentCategory.h"

#include <QDir>
#include <QStandardItemModel>
#include <QWindow>

namespace q2d {
    // forward declaration
    class Application;
    class ApplicationContext;
    class Document;
    namespace metamodel {
    class ComponentCategory;
    }

namespace gui {

// TODO decide: who sets up signal slots between gui elements?
// the UI designer or the code?
class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow*             m_ui;
    q2d::Application*           m_application;
    q2d::ApplicationContext*    m_context;


    void addNewSchematicsTab(Document* relatedDocument);
public:
    explicit MainWindow(ApplicationContext *parent);
    ~MainWindow();

    void setupSignalsAndSlots();

signals:

    // project-related
    void signal_createProjectRequested(QString name);
    void signal_loadProjectRequested(QDir projectDir);
    void signal_unloadProjectRequested();

    // document-related
    void signal_createDocumentRequested(QString name);

    void signal_createCategory(QString name, metamodel::ComponentCategory* parent = 0);
    void signal_loadType(QString fileName, metamodel::ComponentCategory* parent = 0);
    void signal_clearComponentTypes();

    // TODO check visibility
public slots:
    void slot_createProject();
    void slot_loadProject();
    void slot_updateProjectName(QString name);
    void slot_enableProjectSaving(bool enabled = true);
    void slot_enableDocumentMenus(bool enabled = true);
    void slot_setDocumentModel(QStandardItemModel* model);
    void slot_createDocument();
    void slot_openDocumentTab(const QModelIndex index);
    void slot_openDocumentTab(Document* document);
    void slot_setComponentModel(QStandardItemModel* model);

private slots:
    // created by the Qt Designer
    void on_schematicsTabWidget_tabCloseRequested(int index);
    void on_btn_addType_clicked();
    void on_btn_addCategory_clicked();
};

} // namespace gui
} // namespace q2d

#endif // MAINWINDOW_H
