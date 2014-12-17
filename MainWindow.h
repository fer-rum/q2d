// TODO move all related files to gui folder, where it belongs

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "Application.h"
#include "Document.h"

#include "ui_MainWindow.h"

#include <QWindow>

namespace q2d {
    // forward declaration
    class Application;
    class ApplicationContext;
    class Document;

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
    void setDocumentModel(QStandardItemModel* model);

signals:
private slots:
    void slot_updateProjectName(QString name);
    void slot_enableDocumentMenus(bool enabled = true);
    void slot_openDocumentTab(const QModelIndex index);

    void on_schematicsTabWidget_tabCloseRequested(int index);
};

} // namespace gui
} // namespace q2d

#endif // MAINWINDOW_H
