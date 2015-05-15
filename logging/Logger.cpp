#include "Logger.h"

using namespace q2d::logging;

Logger::log(QString message, LogLevel& severity){
    LogEntry* entry = new LogEntry(message, severity);
    m_entries.append(entry);
}

QList<LogEntry>
Logger::entries() const {
    return m_entries;
}
