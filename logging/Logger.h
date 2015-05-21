#ifndef LOGGER_H
#define LOGGER_H

#include <QList>
#include <QObject>
#include <QString>

#include <memory>

namespace q2d {
namespace logging {

class LogEntry;
class LogManager;
class LogLevel;

class Logger
    : public QObject,
        public std::enable_shared_from_this<Logger> {
    Q_OBJECT
friend class LogManager;
private:

    std::shared_ptr<LogManager> m_manager;
    QList<std::shared_ptr<LogEntry>> m_entries;

    /**
     * @brief Logger
     * Loggers may only be created by the LoggerManager.
     * @param name will be stored in the objectName attribute of the QObject
     * @param parent
     */
    Logger(QString name, std::shared_ptr<LogManager> manager, QObject* parent = nullptr);

public:

    void log(QString message, std::shared_ptr<LogLevel> severity);
    void log(QStringList messages, std::shared_ptr<LogLevel> severity);
    void log(QString message, QString severity);
    void log(QStringList messages, QString severity);
    QList<std::shared_ptr<LogEntry>> entries() const;

signals:
    void signal_entryAdded(std::shared_ptr<LogEntry> newEntry, std::shared_ptr<Logger> sender);
};

} // namespace logging
} // namespace q2d

#endif // LOGGER_H
