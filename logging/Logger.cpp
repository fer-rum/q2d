#include "LogEntry.h"
#include "Logger.h"
#include "LogLevel.h"

using namespace q2d::logging;
using namespace std;

Logger::Logger(QString name, QObject* parent)
    : QObject(parent), enable_shared_from_this<Logger>() {
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

QList<std::shared_ptr<LogEntry>>
Logger::entries() const {
    return m_entries;
}
