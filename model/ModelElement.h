#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include <QString>

namespace q2d {
namespace model {

// TODO documentation
// TODO visitor-Pattern
class ModelElement {
private:
    QString name;
public:
    ModelElement(QString name);
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
