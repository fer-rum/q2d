#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"

#include <QList>

namespace q2d {
namespace patterns {

template <class T>
class Observable {
    QList<Observer<T>*> observers;
public:
    Observable(){}
    virtual ~Observable(){}
    void attachObserver(Observer<T> &observer);
    void detachObserver(const Observer<T>& observer);
    void notifyObservers();
};

} // namespace patterns
} // namespace q2d

#endif // OBSERVABLE_H
