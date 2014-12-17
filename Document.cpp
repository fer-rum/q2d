#include "Document.h"

using namespace q2d;

/**
 * @brief Document::Document
 *
 * Upon creation of a document a empty described model
 * and an empty schematic view are created.
 *
 * @param name
 */
Document::Document(QString name, QObject* parent) :
    QObject(parent),
    QStandardItem(name) {

    this->setData(QVariant::fromValue(new model::Model()), DocumentRole::MODEL);
    this->setData(QVariant::fromValue(new view::Schematic(this)), DocumentRole::SCHEMATIC);
}

/**
 * @brief Document::getSchematicView is a convenience function
 * @return
 */
view::Schematic*
Document::getSchematicView(){
    return this->data(DocumentRole::SCHEMATIC).value<view::Schematic*>();
}

/**
 * @brief Document::getDescribedModel is a convenience function
 * @return
 */
model::Model*
Document::getDescribedModel(){
    return this->data(DocumentRole::MODEL).value<model::Model*>();
}
