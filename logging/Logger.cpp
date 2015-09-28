#include "LogEntry.h"
#include "Logger.h"
#include "LogManager.h"
#include "LogLevel.h"

using namespace q2d::logging;

Logger::Logger(QString name, LogManager* manager)
    : QObject(manager) {
    Q_CHECK_PTR(manager);

    m_entries = QList<LogEntry*>();
    this->setObjectName(name);
}

LogManager*
Logger::manager() const {
    return dynamic_cast<LogManager*>(parent());
}

void
Logger::log(QString message, LogLevel* severity) {
    Q_CHECK_PTR(severity);
    LogEntry* newEntry =  new LogEntry(message, severity);
    m_entries.append(newEntry);
    emit signal_entryAdded(newEntry, this);
}

void
Logger::log(QStringList messages, LogLevel* severity) {
    Q_CHECK_PTR(severity);
    foreach(QString s, messages){
        this->log(s, severity);
    }
}

void
Logger::log(QString message, QString severity){
    this->log(message, manager()->logLevel(severity));
}

void
Logger::log(QStringList messages, QString severity){
    this->log(messages, manager()->logLevel(severity));
}

QList<LogEntry*>
Logger::entries() const {
    return m_entries;
}
