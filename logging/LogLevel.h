#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <QColor>
#include <QString>

#include <memory>

namespace q2d {
namespace logging {

class LogManager;

class LogLevel {
    friend class LogManager;
private:
    QString m_name;
    QColor m_fontColor;
    QColor m_backgroundColor;
    std::shared_ptr<LogManager> m_manager;


    // TODO store name in QObjects name property
    /**
     * @brief LogLevel instantiates a new log level.
     * Only the LogManager might instantiate a new LogLevel.
     *
     * @param name is the name under which the log level is known.
     * The name must be unique amongst the used log levels.
     * The name can not be changed once set.
     *
     * The fontColor is the color in which output text for this log level will be rendered
     * (if supported by the output interface).
     * The default font color is black.
     * The backgroundColor is the color in which background for this log level will be rendered
     * (if supported by the output interface).
     * The default background color is white.
     */
    LogLevel(QString name, std::shared_ptr<LogManager> manager);
public:


    QString name() const;
    QColor fontColor() const;
    QColor backgroundColor() const;

    void setFontColor(QColor color);
    void setBackgroundColor(QColor color);


    // constants for naming log levels
    // I found no feasible alternative of enumerating these yet…

    static QString DEBUG;
    static QString ERROR;
    static QString INFO;
    static QString WARNING;
};


} // namespace logging
} // namespace q2d


#endif // LOGLEVEL_H
