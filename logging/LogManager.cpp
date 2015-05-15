#include "LogManager.h"

using namespace mycrqlog;

Logger&
LogManager::logger(QString name) const {

    if(m_loggers.contains(name)){
        return m_loggers.value(name);
    }

    Logger newLogger(name);
    m_loggers.insert(name, newLogger);
    return newLogger;
}

QStringList
LogManager::loggerNames() const {
    return m_loggers.keys();
}

LogLevel&
LogManager::logLevel(QString name) const {

    if(m_logLevels.contains(name)){
        return m_logLevels.value(name);
    }

    LogLevel newLogLevel(name);
    m_logLevels.insert(name, newLogLevel);
    return newLogLevel;

}

QStringList
LogManager::logLevelNames() const {
    return m_logLevels.keys();
}
