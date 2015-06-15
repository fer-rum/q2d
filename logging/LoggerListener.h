#ifndef LOGGERLISTENER_H
#define LOGGERLISTENER_H

#include <QList>
#include <QObject>
#include <QStringList>

namespace q2d {
namespace logging {

class LogEntry;
class Logger;

class LoggerListener
        : public QObject {
    Q_OBJECT
private:

    /**
     * @brief m_listening keeps track of the loggers that are currently listened to.
     */
    QList<Logger*> m_listening;

public:
    explicit LoggerListener(QObject* parent = nullptr);

    /**
     * @brief connect starts receiving a loggers messages.
     * @param logger
     */
    void connect(Logger* logger);

    /**
     * @brief disconnect stops receiving a loggers messages.
     * @param logger
     */
    void disconnect(Logger* logger);

    /**
     * @brief loggers fetches all the loggers that are currently listened to.
     * @return
     */
    QList<Logger* > loggers() const;


    virtual void handleEntry(LogEntry* newEntry, Logger* sender) = 0;

public slots:
    void slot_receiveEntry(LogEntry* newEntry, Logger* sender);
};

} // namespace logging
} // namespace q2d

#endif // LOGGERLISTENER_H
