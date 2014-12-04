#include "MainWindow.h"
#include "ui_MainWindow.h"

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
    connect(this->ui->actionCreate_new_Project, SIGNAL(triggered()), this->context, SLOT(slot_newProject()));
}

void
MainWindow::addNewSchematicsTab(QString title){
    Q_ASSERT(!title.isEmpty());

    // TODO implement better tab?
    QGraphicsScene* scene = new QGraphicsScene();
    this->ui->schematicsTabWidget->addTab(new QGraphicsView(scene), title);
}

void
MainWindow::slot_updateProjectName(QString name){
    this->ui->projectNameLabel->setText(name);
}

void
MainWindow::slot_openDocumentTab(Document *document){

    Q_CHECK_PTR(document);

    this->addNewSchematicsTab(document->getName());
    // TODO connect the schematic with the tab
}
