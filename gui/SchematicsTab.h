#ifndef SCHEMATICSTAB_H
#define SCHEMATICSTAB_H

#include "ui_SchematicsTab.h"

#include "../Document.h"

#include <QWidget>

namespace q2d {

// forward declaration
class Document;

namespace gui {

class SchematicsTab :
    public QWidget {
    Q_OBJECT

public:
    explicit SchematicsTab(QWidget* parent, Document* m_relatedDocument);
    virtual ~SchematicsTab();

private:
    Ui::SchematicsTab* m_ui;
    Document* m_relatedDocument;
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSTAB_H
