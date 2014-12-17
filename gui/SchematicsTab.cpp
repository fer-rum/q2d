#include "SchematicsTab.h"
#include "ui_SchematicsTab.h"

using namespace q2d::gui;

SchematicsTab::SchematicsTab(QWidget *parent, Document* relatedDocument) :
    QWidget(parent),
    ui(new Ui::SchematicsTab) {

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(relatedDocument);

    this->relatedDocument = relatedDocument;
    ui->setupUi(this);
    ui->schematicsView->setScene(relatedDocument->getSchematicView());
    ui->schematicsView->update();


}

SchematicsTab::~SchematicsTab()
{
    delete ui;
}
