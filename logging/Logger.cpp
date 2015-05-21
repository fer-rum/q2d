#include "LogEntry.h"
#include "Logger.h"
#include "LogManager.h"
#include "LogLevel.h"

using namespace q2d::logging;
using namespace std;

Logger::Logger(QString name, std::shared_ptr<LogManager> manager, QObject* parent)
    : QObject(parent),
      enable_shared_from_this<Logger>() {
    m_manager = manager;
    m_entries = QList<std::shared_ptr<LogEntry>>();
    this->setObjectName(name);
}

void
Logger::log(QString message, shared_ptr<LogLevel> severity) {
    shared_ptr<LogEntry> newEntry = shared_ptr<LogEntry>( new LogEntry(message, severity) );
    m_entries.append(newEntry);
    emit signal_entryAdded(newEntry, shared_from_this());
}

void
Logger::log(QStringList messages, shared_ptr<LogLevel> severity) {
    foreach(QString s, messages){
        this->log(s, severity);
    }
}

void
Logger::log(QString message, QString severity){
    this->log(message, m_manager->logLevel(severity));
}

void
Logger::log(QStringList messages, QString severity){
    this->log(messages, m_manager->logLevel(severity));
}

QList<std::shared_ptr<LogEntry>>
Logger::entries() const {
    return m_entries;
}
