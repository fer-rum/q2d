#ifndef LOGGER_H
#define LOGGER_H

#include <QList>
#include <QObject>
#include <QString>

namespace q2d {
namespace logging {

class LogEntry;
class LogManager;
class LogLevel;

class Logger
    : public QObject {
    Q_OBJECT
friend class LogManager;
private:

    LogManager* m_manager;
    QList<LogEntry*> m_entries;

    /**
     * @brief Logger
     * Loggers may only be created by the LoggerManager.
     * @param name will be stored in the objectName attribute of the QObject
     * @param manager is the LogManager that created this instance.
     * It acts as the parent in the QObject hierarchy.
     */
    Logger(QString name, LogManager* manager);

public:

    /**
     * @brief log creates a new LogEntry with the given message and sevetity.
     * The Logger::signal_entryAdded() will be triggered to inform connected listeners.
     * @param message
     * @param severity must not be null.
     */
    void log(QString message, LogLevel* severity);

    /**
     * @brief log creates a new LogEntry from each list entry with given severity.
     * This is a shortcut for calling Logger::log(QString, LogLevel*) upon each list entry.
     * @param messages
     * @param severity must not be null.
     */
    void log(QStringList messages, LogLevel* severity);
    void log(QString message, QString severity);
    void log(QStringList messages, QString severity);
    QList<LogEntry*> entries() const;

signals:
    void signal_entryAdded(LogEntry* newEntry, Logger* sender);
};

} // namespace logging
} // namespace q2d

#endif // LOGGER_H
