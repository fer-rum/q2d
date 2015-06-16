#include "LogManager.h"

using namespace q2d::logging;
using namespace std;

LogManager::LogManager(QApplication* parent)
    : QObject(parent) {
    m_loggers = QMap<QString, Logger*>();
    m_logLevels = QMap<QString, LogLevel*>();
}

Logger*
LogManager::logger(QString name) {

    if(m_loggers.contains(name)){
        return m_loggers.value(name);
    }

    Logger* newLogger = new Logger(name, this);
    m_loggers.insert(name, newLogger);
    return newLogger;
}

QStringList
LogManager::loggerNames() const {
    return m_loggers.keys();
}

LogLevel*
LogManager::logLevel(QString name) {

    if(m_logLevels.contains(name)){
        return m_logLevels.value(name);
    }

    LogLevel* newLogLevel = new LogLevel(name, this);
    m_logLevels.insert(name, newLogLevel);
    return newLogLevel;

}

QStringList
LogManager::logLevelNames() const {
    return m_logLevels.keys();
}
