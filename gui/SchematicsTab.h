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
private:
    Ui::SchematicsTab* m_ui;
    Document* m_relatedDocument;

public:
    explicit SchematicsTab(QWidget* parent, Document* m_relatedDocument);
    virtual ~SchematicsTab();

signals:
    void signal_triggerQuantor(Document* document, QString targetFunction);

private slots:
   void slot_requestedSatSolving();
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSTAB_H
