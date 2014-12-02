#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include "patterns/Observable.h"

#include <QString>


namespace q2d {
namespace model {

// TODO documentation
// TODO visitor-Pattern
class ModelElement : public q2d::patterns::Observable<ModelElement>{
private:
    QString name;
public:
    ModelElement(QString name);
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
