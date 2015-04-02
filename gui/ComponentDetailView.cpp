
#include "../metamodel/ComponentDescriptor.h"
#include "../model/Component.h"
#include "../model/ModelElement.h"
#include "../PortListModel.h"

#include "ComponentDetailView.h"
#include "ui_ComponentDetailView.h"
#include "MainWindow.h"

#include <QStringListModel>

using namespace q2d::gui;

ComponentDetailView::ComponentDetailView(model::Component* component, MainWindow* parent) :
    QDialog(parent),
    m_ui(new Ui::ComponentDetailView) {
    Q_CHECK_PTR(component);
    Q_CHECK_PTR(parent);

    m_ui->setupUi(this);

    this->setWindowTitle(tr("%1 - Details").arg(component->fullId()));
    m_ui->lbl_name->setText(component->localId());
    m_ui->lbl_typeName->setText(component->descriptor()->name());

    util::PortListModel* inPortModel = new util::PortListModel(this);
    inPortModel->setList(component->inputPorts());
    m_ui->list_portsIn->setModel(inPortModel);

    util::PortListModel* outPortModel = new util::PortListModel(this);
    outPortModel->setList(component->outputPorts());
    m_ui->list_portsOut->setModel(outPortModel);

    QStringListModel* functionModel = new QStringListModel(component->functions());
    m_ui->list_functions->setModel(functionModel);
}

ComponentDetailView::~ComponentDetailView() {
    delete m_ui;
}
