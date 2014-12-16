#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "model/Model.h"
#include "view/Schematic.h"

#include <QStandardItem>
#include <QString>

namespace q2d {

// TODO documentation
//     - controller in MVC
// TODO referenced Documents?
// TODO access functions to the model
// TODO description text
class Document : public QStandardItem {
private:
    QString name;
    model::Model* describedModel;
    view::Schematic* view;

public:
    Document(QString name);
    ~Document();

    QString getName();
};

} // namespace q2d

#endif // DOCUMENT_H
