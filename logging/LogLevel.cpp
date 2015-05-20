#include "LogLevel.h"

using namespace q2d::logging;

LogLevel::LogLevel(QString name, QColor fontColor, QColor backgroundColor){
    m_name = name;
    m_fontColor = fontColor;
    m_backgroundColor = backgroundColor;
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
