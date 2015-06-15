#include "LogEntry.h"
#include "Logger.h"
#include "LoggerListener.h"


using namespace q2d::logging;
using namespace std;

LoggerListener::LoggerListener(QObject *parent)
    : QObject(parent) {
    m_listening = QList<Logger*>();
}

void
LoggerListener::connect(Logger* logger){
    if(logger != nullptr){
        this->QObject::connect(logger, &Logger::signal_entryAdded,
                      this, &LoggerListener::slot_receiveEntry);
        m_listening.append(logger);
    }
}

void
LoggerListener::disconnect(Logger* logger){
    if(logger != nullptr){
        this->QObject::disconnect(logger, &Logger::signal_entryAdded,
                              this, &LoggerListener::slot_receiveEntry);
        m_listening.removeAll(logger);
    }
}

QList<Logger*>
LoggerListener::loggers() const {
    return m_listening;
}

void
LoggerListener::slot_receiveEntry(LogEntry*newEntry, Logger* sender){
    this->handleEntry(newEntry, sender);
}
