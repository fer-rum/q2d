#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "LoggerListener.h"

#include <memory>

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

    virtual void handleEntry(std::shared_ptr<LogEntry> newEntry, std::shared_ptr<Logger> sender) override;
};

}   // namespace logging
}   // namespace q2d

#endif // CONSOLELOGGER_H
