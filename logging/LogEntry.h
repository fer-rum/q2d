#ifndef LOGENTRY_H
#define LOGENTRY_H

#include "LogLevel.h"

#include <time.h>
#include <chrono>

namespace mycrqlog {

using std::chrono::steady_clock::time_point;

/**
 * @brief The LogEntry class
 *
 * The steady_clock is used to make sure every log entry has a unique point in time assigned to it.
 */
class LogEntry {
private:

    LogLevel m_severity;

    QString m_message;

    time_point m_timestamp;
public:
    LogEntry(QString message, LogLevel severity);

    QString message() const { return m_message; }
    time_point timestamp() const { return m_timestamp; }
    LogLevel severity() const { return m_severity; }
};

}

#endif // LOGENTRY_H
