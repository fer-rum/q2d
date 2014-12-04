#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "model/Model.h"
#include "view/Schematic.h"

#include <QString>

namespace q2d {

// TODO documentation
//     - controller in MVC
// TODO refernced Documents?
// TODO access functions to the model
class Document {
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
