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
    ui->schematicsView->setScene(relatedDocument->schematic());
    QSize viewSize = ui->schematicsView->size();
    relatedDocument->schematic()->setSceneRect(QRectF(QPoint(0,0), viewSize));
    ui->schematicsView->update();


}

SchematicsTab::~SchematicsTab()
{
    delete ui;
}
