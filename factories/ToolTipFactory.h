#ifndef TOOLTIPFACTORY_H
#define TOOLTIPFACTORY_H

#include <QMap>
#include <QString>

namespace q2d {

class DocumentEntry;

namespace model {
class ModelElement;
class Node;
class Port;
}

namespace factories {

/**
 * @brief The ToolTipFactory class
 * Cooperates with the special model elements of which to generate a tool tip, to form a double dispatch pattern.
 */
class ToolTipFactory {
private:
public:
    /**
     * @brief toHtmlTable renders a Map with String keys and values into an HTML table.
     * @param map
     * @return
     */
    static QString toHtmlTable(const QMap<QString, QString> map);

    // helpers for double dispatch
    static QMap<QString, QString> propertyMap(const model::ModelElement* source);
    static QMap<QString, QString> propertyMap(const model::Node* source);
    static QMap<QString, QString> propertyMap(const model::Port* source);

    static QString generateToolTip(DocumentEntry* entry);
};

} // namespace factories
} // namespace q2d

#endif // TOOLTIPFACTORY_H
