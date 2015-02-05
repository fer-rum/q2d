#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Application.h"
#include "Document.h"
#include "metamodel/Category.h"
#include "ComponentFactory.h"
#include "Constants.h"
#include "gui/SchematicsTab.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QListView>
#include <QGraphicsView>
#include <QMessageBox>

#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::metamodel;

MainWindow::MainWindow(ApplicationContext* parent) :
    QMainWindow(), m_ui(new Ui::MainWindow) {

    Q_CHECK_PTR(parent);
    this->m_context = parent;

    m_ui->setupUi(this);

    this->m_application = qobject_cast<Application*>(Application::instance());
}

MainWindow::~MainWindow() {}

void
MainWindow::setupSignalsAndSlots() {
    Q_CHECK_PTR(m_context);

    // Menus
    connect(m_ui->action_Exit, &QAction::triggered,
            m_application, &Application::quit);
    connect(m_ui->action_createProject, &QAction::triggered,
            this, &MainWindow::slot_createProject);
    connect(m_ui->action_createDocument, &QAction::triggered,
            this, &MainWindow::slot_createDocument);
    connect(m_ui->action_saveProject, &QAction::triggered,
            m_context, &ApplicationContext::signal_saveProject);
    connect(m_ui->action_loadProject, &QAction::triggered,
            this, &MainWindow::slot_loadProject);


    // buttons
    connect(m_ui->btn_newProject, &QPushButton::clicked,
            this, &MainWindow::slot_createProject);
    connect(m_ui->btn_clearHierarchy, &QPushButton::clicked,
            this, &MainWindow::signal_clearComponentTypes);
    connect(m_ui->btn_unloadProject, &QPushButton::clicked,
            this, &MainWindow::signal_unloadProjectRequested);
    connect(m_ui->btn_loadProject, &QPushButton::clicked,
            this, &MainWindow::slot_loadProject);

    // connections to the application context
    // TODO move to applicationContext
    connect(this, &MainWindow::signal_createProjectRequested,
            m_context, &ApplicationContext::slot_newProject);
    connect(this, &MainWindow::signal_createDocumentRequested,
            m_context, &ApplicationContext::slot_newDocument);
    connect(this, &MainWindow::signal_loadProjectRequested,
            m_context, &ApplicationContext::slot_loadProject);
    connect(this, &MainWindow::signal_unloadProjectRequested,
            m_context, &ApplicationContext::slot_unloadProject);
    connect(this, &MainWindow::signal_createCategory,
            m_context, &ApplicationContext::signal_clearComponentTypes);

    // This only needs to be called once since the sender (the ListView)
    // remains the same, even when the model changes
    connect(m_ui->documentListView, &QAbstractItemView::doubleClicked,
            this, static_cast<void (MainWindow::*)(QModelIndex)>
            (&MainWindow::slot_openDocumentTab));

}

void
MainWindow::addNewSchematicsTab(Document* relatedDocument) {
    Q_CHECK_PTR(relatedDocument);

    // TODO check if there is already a tab opened for the document

    SchematicsTab* newTab = new SchematicsTab(this->m_ui->schematicsTabWidget, relatedDocument);
    this->m_ui->schematicsTabWidget->addTab(newTab, relatedDocument->text());

    // TODO connect signals and slots
}

void
MainWindow::slot_createProject() {

    // get name
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Project name required"),
                                         tr("Enter the name of the new project:"),
                                         QLineEdit::Normal, "myProject", &ok);

    if (!ok) { // action canceled
        return;
    }

    // validate name
    if (name.isEmpty()) {
        QMessageBox::critical(this,
                              tr("Error: Project name was empty"),
                              tr("The projects name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    emit this->signal_createProjectRequested(name);
}

void
MainWindow::slot_loadProject() {

    QString dirPath;

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setDirectory(m_application->getSetting(constants::KEY_DIR_PROJECTS).toString());

    int userAction = dialog.exec();
    if (userAction == QDialog::Rejected) {
        return;
    }

    dirPath = dialog.selectedFiles().first();

    emit this->signal_loadProjectRequested(dirPath);
}

void
MainWindow::slot_createDocument() {

    // make sure the model is set up properly
    // so we can enter the documents
    Q_CHECK_PTR(this->m_ui->documentListView->model());

    // get name
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Document name required"),
                                         tr("Enter the name of the new document:"),
                                         QLineEdit::Normal, "myDocument", &ok);

    if (!ok) { // action canceled
        return;
    }

    // validate name
    if (name.isEmpty()) {
        QMessageBox::critical(this,
                              tr("Error: Document name was empty"),
                              tr("The documents name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    emit this->signal_createDocumentRequested(name);
}

void
MainWindow::slot_updateProjectName(QString name) {

    if (name.isEmpty()) {
        name = "(none)";
    }

    this->m_ui->lbl_projectName->setText(name);
}

void
MainWindow::slot_enableProjectSaving(bool enabled) {
    this->m_ui->action_saveProject->setEnabled(enabled);
}

void
MainWindow::slot_enableDocumentMenus(bool enabled) {
    this->m_ui->action_createDocument->setEnabled(enabled);
}

/**
 * @brief MainWindow::setDocumentModel
 *
 * Will be called whe a new q2d::Project is created, to link the projects
 * document model with the appropriate list view in the UI.
 * @param model
 */
void
MainWindow::slot_setDocumentModel(QStandardItemModel* model) {
    qDebug() << "SLOT setDocumentModel(" << model << ")";


    // close all tabs related to the old model
    m_ui->schematicsTabWidget->clear();

    QListView* documentView = m_ui->documentListView;

    documentView->clearSelection();
    QAbstractItemModel* oldModel = documentView->model();

    m_ui->documentListView->setModel(model);

    if (oldModel != nullptr) {
        oldModel->disconnect();
        oldModel->deleteLater();
    }
}

void
MainWindow::slot_openDocumentTab(const QModelIndex index) {
    qDebug() << "SLOT openDocumentTab(" << index.column()
             << ", " << index.row() << ") by " << this->sender();

    // TODO check if there is already a tab open for this index
    // switch to it, if this is the case

    const QStandardItemModel* model =
        static_cast<const QStandardItemModel*>(index.model());
    Q_CHECK_PTR(model);
    Document* document = static_cast<Document*>(model->itemFromIndex(index));
    Q_CHECK_PTR(document);

    this->addNewSchematicsTab(document);
}

void
MainWindow::slot_openDocumentTab(Document* document) {
    this->addNewSchematicsTab(document);
}

void
MainWindow::slot_setComponentModel(QStandardItemModel* model) {
    this->m_ui->componentTreeView->setModel(model);
}

void
MainWindow::on_schematicsTabWidget_tabCloseRequested(int index) {
    this->m_ui->schematicsTabWidget->removeTab(index);
}

void
MainWindow::on_btn_addType_clicked() {


    Q_CHECK_PTR(this->m_ui->componentTreeView->model());

    ComponentFactory* componentFactory = this->m_context->componentFactory();

    // get the currently selected entry as parent (if eligible)
    QModelIndex currentIndex = m_ui->componentTreeView->currentIndex();
    Category* parent = componentFactory->getCategoryForIndex(currentIndex);

    QString fileName;

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter(tr("Component Descriptions (*.json)"));
    dialog.setDirectory(this->m_application->getSetting(constants::KEY_DIR_COMPONENTS).toString());

    int userAction = dialog.exec();
    if (userAction == QDialog::Rejected) {
        return;
    }

    fileName = dialog.selectedFiles().first();
    qDebug() << "Selected " << fileName;

    emit this->signal_loadType(fileName, parent);
}

void
MainWindow::on_btn_addCategory_clicked() {

    Q_CHECK_PTR(this->m_ui->componentTreeView->model());

    ComponentFactory* componentFactory = this->m_context->componentFactory();

    // get the currently selected entry as parent (if eligible)
    QModelIndex currentIndex = m_ui->componentTreeView->currentIndex();
    Category* parent = componentFactory->getCategoryForIndex(currentIndex);

    // get the name for the new category
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Category name required"),
                                         tr("Enter the name of the new component category:"),
                                         QLineEdit::Normal, "myCategory", &ok);

    if (!ok) { // action canceled
        return;
    }

    // validate name
    if (name.isEmpty()) {
        QMessageBox::critical(this,
                              tr("Error: Category name was empty"),
                              tr("The categories name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    // add a new category
    emit this->signal_createCategory(name, parent);
}
