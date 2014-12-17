#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "gui/SchematicsTab.h"

#include <QGraphicsView>

using namespace q2d::gui;

MainWindow::MainWindow(ApplicationContext* parent) :
    QMainWindow(), ui(new Ui::MainWindow){

    Q_CHECK_PTR(parent);
    this->context = parent;

    ui->setupUi(this);

    this->application = qobject_cast<Application*>(Application::instance());
}

MainWindow::~MainWindow() {}

void
MainWindow::setupSignalsAndSlots(){
    Q_CHECK_PTR(this->context);

    // Menus
    connect(this->ui->actionExit, SIGNAL(triggered()), this->application, SLOT(quit()));
    connect(this->ui->action_createProject, SIGNAL(triggered()), this->context, SLOT(slot_newProject()));
    connect(this->ui->action_createDocument, SIGNAL(triggered()), this->context, SLOT(slot_newDocument()));
}

/**
 * @brief MainWindow::setDocumentModel
 *
 * Will be called whe a new q2d::Project is created, to link the projects
 * document model with the appropriate list view in the UI.
 * @param model
 */
void
MainWindow::setDocumentModel(QStandardItemModel* model){

    Q_CHECK_PTR(model);

    this->ui->documentListView->setModel(model);

    connect(this->ui->documentListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_openDocumentTab(QModelIndex)));
}

void
MainWindow::addNewSchematicsTab(Document* relatedDocument){
    Q_CHECK_PTR(relatedDocument);

    SchematicsTab* newTab = new SchematicsTab(this->ui->schematicsTabWidget, relatedDocument);
    this->ui->schematicsTabWidget->addTab(newTab, relatedDocument->text());

    // TODO connect signals and slots
}

void
MainWindow::slot_updateProjectName(QString name){
    this->ui->projectNameLabel->setText(name);
}

void
MainWindow::slot_enableDocumentMenus(bool enabled){
    this->ui->action_createDocument->setEnabled(enabled);
}

void
MainWindow::slot_openDocumentTab(const QModelIndex index){

    Project* currentProject = this->context->getCurrentProject();
    Q_CHECK_PTR(currentProject);
    QStandardItem* item = currentProject->getDocuments()->itemFromIndex(index);
    Document* document = static_cast<Document*>(item);
    Q_CHECK_PTR(document);

    // TODO check if there is already a tab opened for the document

    this->addNewSchematicsTab(document);
}

void q2d::gui::MainWindow::on_schematicsTabWidget_tabCloseRequested(int index) {
    this->ui->schematicsTabWidget->removeTab(index);
}
