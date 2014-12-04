#include "Document.h"

using namespace q2d;

// NOTE upon creation of a Ducument, an empty Model and Schematic is created
Document::Document(QString name) {
    this->describedModel = new model::Model(name);
    this->view = new view::Schematic();
}

// NOTE delete the Model and Schematics
// TODO who needs to know about these deletions?
Document::~Document(){
    delete this->describedModel;
    delete this->view;
}

QString
Document::getName(){
    return this->name;
}
