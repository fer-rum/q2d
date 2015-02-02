#include "SchematicsTab.h"
#include "ui_SchematicsTab.h"

using namespace q2d::gui;

SchematicsTab::SchematicsTab(QWidget *parent, Document* relatedDocument) :
    QWidget(parent),
    m_ui(new Ui::SchematicsTab) {

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(relatedDocument);

    m_relatedDocument = relatedDocument;
    m_ui->setupUi(this);
    m_ui->schematicsView->setScene(relatedDocument->schematic());
    QSize viewSize = m_ui->schematicsView->size();
    relatedDocument->schematic()->setSceneRect(QRectF(QPoint(0,0), viewSize));
    m_ui->schematicsView->update();


}

SchematicsTab::~SchematicsTab(){
    delete m_ui;
    // do not delete the document…
}
