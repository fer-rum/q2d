
#include "../model/Component.h"
#include "../PortListModel.h"

#include "ComponentDetailView.h"
#include "ui_ComponentDetailView.h"
#include "MainWindow.h"

using namespace q2d::gui;

ComponentDetailView::ComponentDetailView(model::Component* component, MainWindow *parent) :
    QDialog(parent),
    m_ui(new Ui::ComponentDetailView) {
    Q_CHECK_PTR(component);
    Q_CHECK_PTR(parent);

    m_ui->setupUi(this);
    util::PortListModel* inPortModel = new util::PortListModel(this);
    inPortModel->setList(component->inputPorts());
    m_ui->list_portsIn->setModel(inPortModel);

    util::PortListModel* outPortModel = new util::PortListModel(this);
    outPortModel->setList(component->outputPorts());
    m_ui->list_portsOut->setModel(outPortModel);
}

ComponentDetailView::~ComponentDetailView(){
    delete m_ui;
}
