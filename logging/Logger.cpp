#include "Logger.h"

using namespace mycrqlog;

Logger::log(QString message, LogLevel& severity){
    LogEntry* entry = new LogEntry(message, severity);
    m_entries.append(entry);
}
