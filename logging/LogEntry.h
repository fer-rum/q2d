#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QString>

#include <chrono>
#include <memory>

namespace q2d {
namespace logging {

class LogLevel;

/**
 * @brief The LogEntry class
 *
 * The steady_clock is used to make sure every log entry has a unique point in time assigned to it.
 */
class LogEntry {
private:

    std::shared_ptr<LogLevel> m_logLevel;

    QString m_message;

    std::chrono::time_point<std::chrono::steady_clock> m_timestamp;
public:
    LogEntry(QString message, std::shared_ptr<LogLevel> logLevel);

    QString message() const;
    std::chrono::time_point<std::chrono::steady_clock> timestamp() const;
    std::shared_ptr<LogLevel> logLevel() const;
};

} // namespace logging
} // namespace q2d

#endif // LOGENTRY_H
