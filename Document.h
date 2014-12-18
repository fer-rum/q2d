#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "model/Model.h"
#include "view/Schematic.h"

#include <QObject>
#include <QStandardItem>
#include <QString>

namespace q2d {

enum DocumentRole {
    MODEL = Qt::UserRole + 1000,
    SCHEMATIC = Qt::UserRole + 1001
};

// TODO documentation
//     - controller in MVC
// TODO referenced Documents?
// TODO description text
// TODO saving
// TODO loading

class Document :
        public QObject,
        public QStandardItem {
    Q_OBJECT
private:

public:
    explicit Document(QString name, QObject* parent = 0);

    view::Schematic* getSchematicView();
    model::Model* getDescribedModel();
};

} // namespace q2d

// metatype declaration for the contents of the document
// so these things can be used as data
Q_DECLARE_METATYPE(q2d::model::Model*)
Q_DECLARE_METATYPE(q2d::view::Schematic*)

#endif // DOCUMENT_H
