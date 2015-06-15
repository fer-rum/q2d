#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "LoggerListener.h"

namespace q2d {
namespace logging {

/**
 * @brief The ConsoleLogger class is a logger that prints out all listened to Loggers on stdout.
 */
class ConsoleLogger
        : public LoggerListener
{
public:
    ConsoleLogger(QObject* parent = nullptr);

    virtual void handleEntry(LogEntry* newEntry, Logger* sender) override;
};

}   // namespace logging
}   // namespace q2d

#endif // CONSOLELOGGER_H
