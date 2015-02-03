#ifndef OBSERVER_H
#define OBSERVER_H

namespace q2d {
namespace patterns {

// TODO stub
template <class T>
class Observer {
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void update(T* observed) = 0;
};

} // namespace patterns
} // namespace q2d

#endif // OBSERVER_H
