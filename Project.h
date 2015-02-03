#ifndef PROJECT_H
#define PROJECT_H


#include "Document.h"

#include <QDir>
#include <QList>
#include <QObject>
#include <QSettings>
#include <QString>

namespace q2d {

// forward declaration
class ApplicationContext;

// TODO documentation
// TODO saving
// TODO loading
class Project : public QObject {
    Q_OBJECT
private:
    ApplicationContext* m_applicationContext;
    QString             m_name;
    QStandardItemModel  m_documents;
    QSettings           m_projectSettings;

    void save(QDir projectDirectory);
public:
    Project(QString name, ApplicationContext* parent = nullptr);

    QStandardItemModel* getDocuments();

    void createDocument(QString m_name);
// TODO    void deleteDocument(Document &toDelete);

    void setupSignalsAndSlots();

signals:
    void signal_showDocument(Document* document);
    void signal_nameChanged(QString newName);

public slots:
    void slot_newDocument(QString m_name);
    void slot_save();

};

} // namespace q2d

#endif // PROJECT_H
