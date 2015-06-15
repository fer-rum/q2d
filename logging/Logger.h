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
     * @param parent
     */
    Logger(QString name, LogManager* manager, QObject* parent = nullptr);

public:

    void log(QString message, LogLevel* severity);
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
