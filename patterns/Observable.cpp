
#include "Observable.h"

using namespace q2d::patterns;

// TODO this belongs into a header

template <class T>
void
Observable<T>::attachObserver(Observer<T> &observer) {
    if (!this->observers.contains(observer)) {
        this->observers.append(observer);
    }
}

template <class T>
void
Observable<T>::detachObserver(Observer<T> const &observer) {
    this->observers.removeAll(observer);
}

template <class T>
void
Observable<T>::notifyObservers() {
    for (typename QList<Observer<T>*>::iterator current = this->observers.begin();
            current != this->observers.end();
            current++) {

        (*current)->update(this);
    }
}
