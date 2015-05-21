#include "LogManager.h"
#include "LogLevel.h"


using namespace q2d::logging;
using namespace std;

QString LogLevel::DEBUG = "Debug";
QString LogLevel::ERROR = "Error";
QString LogLevel::INFO = "Info";
QString LogLevel::WARNING = "Warning";

LogLevel::LogLevel(QString name, shared_ptr<LogManager> manager){
    m_name = name;
    m_manager = manager;
    m_fontColor = Qt::black;
    m_backgroundColor = Qt::white;
}

QString
LogLevel::name() const {
    return m_name;
}

QColor
LogLevel::fontColor() const {
    return m_fontColor;
}

QColor
LogLevel::backgroundColor() const {
    return m_backgroundColor;
}

void
LogLevel::setFontColor(QColor color){
    m_fontColor = color;
}

void
LogLevel::setBackgroundColor(QColor color){
    m_backgroundColor = color;
}
