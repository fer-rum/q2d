#include "SchematicsTab.h"
#include "ui_SchematicsTab.h"

#include "../Constants.h"
#include "../Application.h"

#include <QDrag>
#include <QMessageBox>
#include <QMimeData>
#include <QInputDialog>
#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::constants;

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

    // connect all the buttons
    connect(m_ui->btn_solve, &QPushButton::clicked,
            this, &SchematicsTab::slot_requestedSatSolving);
    connect(m_ui->btn_addInPort, &QToolButton::clicked,
            this, &SchematicsTab::slot_addInPortButtonClicked);
    connect(m_ui->btn_addOutPort, &QToolButton::clicked,
            this, &SchematicsTab::slot_addOutPortButtonClicked);
    connect(relatedDocument->schematic(), &Schematic::signal_mousePosChanged,
            this, &SchematicsTab::signal_mousePosChanged);

    // TODO set up sel_direction properly to avoid nasty string comparison when reading its state
}

SchematicsTab::~SchematicsTab() {
    delete m_ui;
    // do not delete the document…
}

QString
SchematicsTab::requestPortName(){
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Port name required"),
                                         tr("Enter the name of the new port:"),
                                         QLineEdit::Normal, "myPort", &ok);

    if (!ok) { // action canceled
        throw QString("Action canceled");
    }

    // validate name
    if (name.isEmpty()) {
        QMessageBox::critical(this,
                              tr("Error: Port name was empty"),
                              tr("The ports name must not be empty."),
                              QMessageBox::Ok);
        throw QString("Name was empty");
    }

    return name;
}

void
SchematicsTab::initiatePortDrag(model::enums::PortDirection portDirection){
    QString name;
    try {
        name = this->requestPortName();
    } catch( QString msg) {
        qDebug() << msg;
        return;
    }

    // start a drag, so the port can be dropped at the desired location
    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();

    QIcon icon;
    QString directionString = model::enums::PortDirectionToString(portDirection);
    // create the pixmap for the drag operation
    switch(portDirection){
    case model::enums::PortDirection::IN :
        icon = QIcon(":/icons/ressources/icons/outside_port_in.svg");
        break;
    case model::enums::PortDirection::OUT :
        icon = QIcon(":/icons/ressources/icons/outside_port_out.svg");
        break;
    default: // should not happen
        Q_ASSERT(false);
    }

    // getting the size is a hack for now
    // there should be a proper way to implement it
    QPixmap iconPixmap = icon.pixmap(ICON_SIZE);

    mimeData->setData(MIME_PORT_PLACEMENT, directionString.toUtf8());
    mimeData->setText(name);
    drag->setMimeData(mimeData);
    drag->setPixmap(iconPixmap);
    drag->exec();
}

void
SchematicsTab::slot_requestedSatSolving() {

    // FIXME: Instead of a edit line, this should request the function
    // after the button was clicked, to avoid cluttering the tab.
    // Which would depend on variable tracking
    // TODO implement a more comfortable "edit function window"
    QString targetFunction = m_ui->input_function->text();

    if (targetFunction.isEmpty()) {
        QMessageBox::warning(this, tr("Function was empty"),
                             tr("The given function string was empty. "
                                "This is trivially satisfiable with any configuration."),
                             QMessageBox::Ok);
        return;
    }

    emit signal_triggerQuantor(m_relatedDocument, targetFunction);
}

void
SchematicsTab::slot_addInPortButtonClicked() {
    this->initiatePortDrag(model::enums::PortDirection::IN);
}

void
SchematicsTab::slot_addOutPortButtonClicked() {
    this->initiatePortDrag(model::enums::PortDirection::OUT);
}


