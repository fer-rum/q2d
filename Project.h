#ifndef PROJECT_H
#define PROJECT_H

#include "ApplicationContext.h"
#include "Document.h"

#include <QList>
#include <QObject>
#include <QSettings>
#include <QString>

namespace q2d {

    // forward declaration
    class ApplicationContext;

// TODO documentation
// TODO implementation
class Project : public QObject {
    Q_OBJECT
private:
    QString name;
    QList<Document*> documents;
    QSettings projectSettings;



public:
    Project(QString name, ApplicationContext *parent = 0);
// TODO    void createDocument(QString name);
// TODO    void deleteDocument(Document &toDelete);

signals:
    void signal_nameChanged(QString newName);

public slots:
// TODO    void slot_newDocument();

};

} // namespace q2d

#endif // PROJECT_H
