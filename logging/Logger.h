#ifndef LOGGER_H
#define LOGGER_H

#include <QList>
#include <QObject>
#include <QString>

#include <memory>

namespace q2d {
namespace logging {

class LogEntry;
class LogLevel;

class Logger
    : public QObject,
        public std::enable_shared_from_this<Logger> {
    Q_OBJECT

private:

    QList<std::shared_ptr<LogEntry>> m_entries;

public:
    /**
     * @brief Logger
     * @param name will be stored in the objectName attribute of the QObject
     * @param parent
     */
    Logger(QString name, QObject* parent = nullptr);
    void log(QString message, std::shared_ptr<LogLevel> severity);
    void log(QStringList messages, std::shared_ptr<LogLevel> severity);
    QList<std::shared_ptr<LogEntry>> entries() const;

signals:
    void signal_entryAdded(std::shared_ptr<LogEntry> newEntry, std::shared_ptr<Logger> sender);
};

} // namespace logging
} // namespace q2d

#endif // LOGGER_H
