#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "Logger.h"
#include "LogLevel.h"

#include <QApplication>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>

namespace q2d {
namespace logging {

/**
 * @brief The LogManager class
 * The log manager is tied to a QApplication as a parent and should be instantiated by such.
 */
class LogManager :
    public QObject {
    Q_OBJECT
private:

    QMap<QString, Logger*> m_loggers;
    QMap<QString, LogLevel*> m_logLevels;

public:

    LogManager(QApplication* parent);

    /**
     * @brief logger will get the logger with the given name
     * or create a new one, if a logger with the given name does not exist.
     * @param name
     * @return
     */
    Logger* logger(QString name);

    QStringList loggerNames() const;

    /**
     * @brief logLevel will get the log level with the given name
     * or create a new one, if a log level with the given name does not exist.
     * If the log level is created anew, its default color is white.
     * @param name
     * @return
     */
    LogLevel* logLevel(QString name);

    QStringList logLevelNames() const;
};

} // namespace logging
 // namespace q2d
}

#endif // LOGMANAGER_H
