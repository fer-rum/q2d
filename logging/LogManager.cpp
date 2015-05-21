#include "LogManager.h"

using namespace q2d::logging;
using namespace std;

LogManager::LogManager(QObject* parent)
    : QObject(parent),
    enable_shared_from_this<LogManager>(){}

shared_ptr<Logger>
LogManager::logger(QString name) {

    if(m_loggers.contains(name)){
        return m_loggers.value(name);
    }

    shared_ptr<Logger> newLogger( new Logger(name, shared_from_this()) );
    m_loggers.insert(name, newLogger);
    return newLogger;
}

QStringList
LogManager::loggerNames() const {
    return m_loggers.keys();
}

shared_ptr<LogLevel>
LogManager::logLevel(QString name) {

    if(m_logLevels.contains(name)){
        return m_logLevels.value(name);
    }

    shared_ptr<LogLevel> newLogLevel( new LogLevel(name, shared_from_this()) );
    m_logLevels.insert(name, newLogLevel);
    return newLogLevel;

}

QStringList
LogManager::logLevelNames() const {
    return m_logLevels.keys();
}
