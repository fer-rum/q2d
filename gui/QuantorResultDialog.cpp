#include "QuantorResultDialog.h"
#include "ui_QuantorResultDialog.h"

#include "../MapModel.h"

#include <QAbstractTableModel>

QuantorResultDialog::QuantorResultDialog(QWidget* parent, QString resultText,
        const QMap<QString, bool>* resultMapping) :
    QDialog(parent),
    m_ui(new Ui::QuantorResultDialog) {
    m_ui->setupUi(this);
    m_ui->lbl_resultText->setText(resultText);
    q2d::util::MapModel* model = new q2d::util::MapModel(this);
    model->setMap(resultMapping);
    m_ui->table_Assignments->setModel(model);
}

QuantorResultDialog::~QuantorResultDialog() {
    m_ui->table_Assignments->model()->deleteLater();
    delete m_ui;
}
