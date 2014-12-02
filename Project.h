#ifndef PROJECT_H
#define PROJECT_H

#include "Document.h"

#include <QList>
#include <QSettings>
#include <QString>

namespace q2d {

// TODO documentation
// TODO implementation
class Project {
private:
    QString name;
    QList<Document*> documents;
    QSettings projectSettings;

public:
    Project(QString name);
    void createDocument(QString name);
    void deleteDocument(Document &toDelete);
};

} // namespace q2d

#endif // PROJECT_H
