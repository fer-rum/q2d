#include "LogEntry.h"
#include "Logger.h"
#include "LoggerListener.h"


using namespace q2d::logging;
using namespace std;

LoggerListener::LoggerListener(QObject *parent)
    : QObject(parent) {
    m_listening = QList<shared_ptr<Logger>>();
}

void
LoggerListener::connect(std::shared_ptr<Logger> logger){
    if(logger){
        this->QObject::connect(logger.get(), &Logger::signal_entryAdded,
                      this, &LoggerListener::slot_receiveEntry);
        m_listening.append(logger);
    }
}

void
LoggerListener::disconnect(std::shared_ptr<Logger> logger){
    this->QObject::disconnect(logger.get(), &Logger::signal_entryAdded,
                              this, &LoggerListener::slot_receiveEntry);
    m_listening.removeAll(logger);
}

QList<shared_ptr<Logger>>
LoggerListener::loggers() const {
    return m_listening;
}

void
LoggerListener::slot_receiveEntry(std::shared_ptr<LogEntry> newEntry, shared_ptr<Logger> sender){
    this->handleEntry(newEntry, sender);
}
