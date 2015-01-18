// TODO move all related files to gui folder, where it belongs

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include "metamodel/ComponentCategory.h"

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

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    q2d::Application* application;
    q2d::ApplicationContext* context;


    void addNewSchematicsTab(Document* relatedDocument);
public:
    explicit MainWindow(ApplicationContext *parent);
    ~MainWindow();

    void setupSignalsAndSlots();

signals:

    void signal_createProjectRequested(QString name);
    void signal_createDocumentRequested(QString name);

    void signal_createCategory(QString name, metamodel::ComponentCategory* parent = 0);
    void signal_loadType(QString fileName, metamodel::ComponentCategory* parent = 0);

    // TODO check visibility
public slots:
    void slot_createProject();
    void slot_updateProjectName(QString name);
    void slot_enableDocumentMenus(bool enabled = true);
    void slot_setDocumentModel(QStandardItemModel* model);
    void slot_createDocument();
    void slot_openDocumentTab(const QModelIndex index);
    void slot_openDocumentTab(Document* document);
    void slot_setComponentModel(QStandardItemModel* model);

    // created by the Qt Designer
    void on_schematicsTabWidget_tabCloseRequested(int index);
    void on_addTypeButton_clicked();
    void on_addCategoryButton_clicked();
private slots:
};

} // namespace gui
} // namespace q2d

#endif // MAINWINDOW_H
