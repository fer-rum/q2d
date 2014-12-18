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

    Project* currentProject = this->context->getCurrentProject();
    Q_CHECK_PTR(currentProject);
    QStandardItem* item = currentProject->getDocuments()->itemFromIndex(index);
    Document* document = static_cast<Document*>(item);
    Q_CHECK_PTR(document);

    // TODO check if there is already a tab opened for the document

    this->addNewSchematicsTab(document);
}

void
MainWindow::slot_setComponentModel(QStandardItemModel* model){
    this->ui->componentTreeView->setModel(model);
}

void q2d::gui::MainWindow::on_schematicsTabWidget_tabCloseRequested(int index) {
    this->ui->schematicsTabWidget->removeTab(index);
}

void q2d::gui::MainWindow::on_addTypeButton_clicked()
{
    // TODO
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
    // TODO via signals
    componentFactory->addCategory(name, parent);
}
