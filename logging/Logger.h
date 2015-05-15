#ifndef LOGGER_H
#define LOGGER_H

#include "LogEntry.h"
#include "LogLevel.h"

#include <QList>
#include <QString>

namespace q2d {
namespace logging {

class Logger {
private:

    /**
     * @brief m_name is the name under which the logger will be known.
     * Usually this is a class or module name.
     */
    QString m_name;
    QList<LogEntry> m_entries;

public:
    void log(QString message, LogLevel& severity);
    QList<LogEntry> entries() const { return m_entries; }

};

} // namespace logging
} // namespace q2d

#endif // LOGGER_H
