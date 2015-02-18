#include "SchematicsTab.h"
#include "ui_SchematicsTab.h"

#include <QMessageBox>

using namespace q2d::gui;

SchematicsTab::SchematicsTab(QWidget* parent, Document* relatedDocument) :
    QWidget(parent),
    m_ui(new Ui::SchematicsTab) {

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(relatedDocument);

    m_relatedDocument = relatedDocument;
    m_ui->setupUi(this);
    m_ui->schematicsView->setScene(relatedDocument->schematic());
    QSize viewSize = m_ui->schematicsView->size();
    relatedDocument->schematic()->setSceneRect(QRectF(QPoint(0, 0), viewSize));
    m_ui->schematicsView->update();

    connect(m_ui->btn_solve, &QPushButton::clicked,
            this, &SchematicsTab::slot_requestedSatSolving);
}

SchematicsTab::~SchematicsTab() {
    delete m_ui;
    // do not delete the document…
}

void
SchematicsTab::slot_requestedSatSolving(){

    QString targetFunction = m_ui->input_function->text();

    if(targetFunction.isEmpty()){
        QMessageBox::warning(this, tr("Function was empty"),
                             tr("The given function string was empty. "
                                "This is trivially satisfiable with any configuration."),
                             QMessageBox::Ok);
        return;
    }

    emit signal_triggerQuantor(m_relatedDocument, targetFunction);
}
