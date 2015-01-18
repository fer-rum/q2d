#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Application.h"
#include "Document.h"
#include "metamodel/ComponentCategory.h"
#include "ComponentFactory.h"
#include "Constants.h"
#include "gui/SchematicsTab.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QGraphicsView>
#include <QMessageBox>

#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::metamodel;

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

    // TODO new style connections
    // TODO move to ApplicationContext?

    // Menus
    connect(this->ui->actionExit, SIGNAL(triggered()), this->application, SLOT(quit()));
    connect(this->ui->action_createProject, SIGNAL(triggered()), this, SLOT(slot_createProject()));
    connect(this->ui->action_createDocument, SIGNAL(triggered()), this, SLOT(slot_createDocument()));

    // buttons
    connect(this->ui->newProjectButton, SIGNAL(clicked()), this, SLOT(slot_createProject()));

    // connections to the application context
    connect(this, SIGNAL(signal_createProjectRequested(QString)), this->context, SLOT(slot_newProject(QString)));
    connect(this, SIGNAL(signal_createDocumentRequested(QString)), this->context, SLOT(slot_newDocument(QString)));
}

void
MainWindow::addNewSchematicsTab(Document* relatedDocument){
    Q_CHECK_PTR(relatedDocument);

    // TODO check if there is already a tab opened for the document

    SchematicsTab* newTab = new SchematicsTab(this->ui->schematicsTabWidget, relatedDocument);
    this->ui->schematicsTabWidget->addTab(newTab, relatedDocument->text());

    // TODO connect signals and slots
}

void
MainWindow::slot_createProject(){

    // get name
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Project name required"),
                                         tr("Enter the name of the new project:"),
                                         QLineEdit::Normal, "myProject", &ok);

    if(!ok){ // action canceled
        return;
    }

    // validate name
    if(name.isEmpty()){
        QMessageBox::critical(this,
                              tr("Error: Project name was empty"),
                              tr("The projects name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    emit this->signal_createProjectRequested(name);
}

void
MainWindow::slot_createDocument(){

    // make sure the model is set up properly
    // so we can enter the documents
    Q_CHECK_PTR(this->ui->documentListView->model());

    // get name
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Document name required"),
                                         tr("Enter the name of the new document:"),
                                         QLineEdit::Normal, "myDocument", &ok);

    if(!ok){ // action canceled
        return;
    }

    // validate name
    if(name.isEmpty()){
        QMessageBox::critical(this,
                              tr("Error: Document name was empty"),
                              tr("The documents name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    emit this->signal_createDocumentRequested(name);
}

void
MainWindow::slot_updateProjectName(QString name){
    this->ui->projectNameLabel->setText(name);
}

void
MainWindow::slot_enableDocumentMenus(bool enabled){
    this->ui->action_createDocument->setEnabled(enabled);
}

/**
 * @brief MainWindow::setDocumentModel
 *
 * Will be called whe a new q2d::Project is created, to link the projects
 * document model with the appropriate list view in the UI.
 * @param model
 */
void
MainWindow::slot_setDocumentModel(QStandardItemModel* model){

    Q_CHECK_PTR(model);

    this->ui->documentListView->setModel(model);

    connect(this->ui->documentListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_openDocumentTab(QModelIndex)));
}

void
MainWindow::slot_openDocumentTab(const QModelIndex index){

    const QStandardItemModel* model = static_cast<const QStandardItemModel*>(index.model());
    Q_CHECK_PTR(model);
    Document* document = static_cast<Document*>(model->itemFromIndex(index));
    Q_CHECK_PTR(document);

    this->addNewSchematicsTab(document);
}

void
MainWindow::slot_openDocumentTab(Document* document){
    this->addNewSchematicsTab(document);
}

void
MainWindow::slot_setComponentModel(QStandardItemModel* model){
    this->ui->componentTreeView->setModel(model);
}

void q2d::gui::MainWindow::on_schematicsTabWidget_tabCloseRequested(int index) {
    this->ui->schematicsTabWidget->removeTab(index);
}

void q2d::gui::MainWindow::on_addTypeButton_clicked() {


    Q_CHECK_PTR(this->ui->componentTreeView->model());

    ComponentFactory* componentFactory = this->context->getComponentFactory();

    // get the currently selected entry as parent (if eligible)
    QModelIndex currentIndex = ui->componentTreeView->currentIndex();
    ComponentCategory* parent = componentFactory->getCategoryForIndex(currentIndex);

    QString fileName;

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter(tr("Component Descriptions (*.json)"));
    dialog.setDirectory(this->application->getSetting(constants::KEY_COMPONENTS_DIR).toString());

    int userAction = dialog.exec();
    if(userAction == QDialog::Rejected){
        return;
    }

    fileName = dialog.selectedFiles().first();
    qDebug() << "Selected " << fileName;

    emit this->signal_loadType(fileName, parent);
}

void q2d::gui::MainWindow::on_addCategoryButton_clicked() {

    Q_CHECK_PTR(this->ui->componentTreeView->model());

    ComponentFactory* componentFactory = this->context->getComponentFactory();

    // get the currently selected entry as parent (if eligible)
    QModelIndex currentIndex = ui->componentTreeView->currentIndex();
    ComponentCategory* parent = componentFactory->getCategoryForIndex(currentIndex);

    // get the name for the new category
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Category name required"),
                                         tr("Enter the name of the new component category:"),
                                         QLineEdit::Normal, "myCategory", &ok);

    if(!ok){ // action canceled
        return;
    }

    // validate name
    if(name.isEmpty()){
        QMessageBox::critical(this,
                              tr("Error: Category name was empty"),
                              tr("The categories name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    // add a new category
    emit this->signal_createCategory(name, parent);
}
