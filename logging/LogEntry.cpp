#include "LogEntry.h"
#include "LogLevel.h"

using namespace q2d::logging;
using namespace std;

LogEntry::LogEntry(QString message, shared_ptr<LogLevel> logLevel){
    m_message = message;
    m_logLevel = logLevel;
    m_timestamp = chrono::steady_clock::now();
}

QString LogEntry::message() const {
    return m_message;
}

chrono::time_point<chrono::steady_clock>
LogEntry::timestamp() const {
    return m_timestamp;
}

shared_ptr<LogLevel>
LogEntry::logLevel() const {
    return m_logLevel;
}
