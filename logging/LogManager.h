#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "Logger.h"
#include "LogLevel.h"

#include <QString>
#include <QStringList>
#include <QMap>
#include <QObject>

#include <memory>

namespace q2d {
namespace logging {

class LogManager :
    public QObject {
    Q_OBJECT

private:

    QMap<QString, std::shared_ptr<Logger>> m_loggers;
    QMap<QString, std::shared_ptr<LogLevel>> m_logLevels;

public:

    LogManager(QObject* parent = nullptr);

    /**
     * @brief logger will get the logger with the given name
     * or create a new one, if a logger with the given name does not exist.
     * @param name
     * @return
     */
    std::shared_ptr<Logger> logger(QString name);

    QStringList loggerNames() const;

    /**
     * @brief logLevel will get the log level with the given name
     * or create a new one, if a log level with the given name does not exist.
     * If the log level is created anew, its default color is white.
     * @param name
     * @return
     */
    std::shared_ptr<LogLevel> logLevel(QString name);

    QStringList logLevelNames() const;
};

} // namespace logging
 // namespace q2d
}

#endif // LOGMANAGER_H
