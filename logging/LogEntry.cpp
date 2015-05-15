#include "LogEntry.h"

using namespace q2d::logging;
using std::chrono::steady_clock::time_point;

LogEntry::LogEntry(QString message, LogLevel logLevel){
    m_message = message;
    m_logLevel = severity;
    m_timestamp = time(nullptr);
}

QString LogEntry::message() const {
    return m_message;
}

time_point
LogEntry::timestamp() const {
    return m_timestamp;
}

LogLevel
LogEntry::logLevel() const {
    return m_logLevel;
}
