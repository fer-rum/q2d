#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <QColor>
#include <QString>

namespace q2d {
namespace logging {

class LogLevel {
private:
    QString m_name;
    QColor m_fontColor;
    QColor m_backgroundColor;

public:
    /**
     * @brief LogLevel instantiates a new log level.
     * @param name is the name under which the log level is known.
     * The name must be unique amongst the used log levels.
     * The name can not be changed once set.
     * @param fontColor is the color in which output text for this log level will be rendered
     * (if supported by the output interface).
     * The default font color is black.
     * @param backgroundColor is the color in which background for this log level will be rendered
     * (if supported by the output interface).
     * The default background color is white.
     */
    LogLevel(QString name, QColor fontColor = Qt::black, QColor backgroundColor = Qt::white);

    QString name() const;
    QColor fontColor() const;
    QColor backgroundColor() const;
};


} // namespace logging
} // namespace q2d


#endif // LOGLEVEL_H
