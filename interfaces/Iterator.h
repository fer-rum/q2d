#ifndef ITERATOR_H
#define ITERATOR_H

#include <QtDebug>

namespace q2d {
namespace quantor {

// TODO the iterator needs to know if it has ownership of the iterated structure
// if this is the case it has to delete the owned structure

/**
 *  This class has been introduced for TBP-code compatibility.
 */
template<typename ElementType>
class Iterator {
private:
    ElementType const* m_current;
    ElementType const* m_end;

public:

    Iterator(ElementType const* begin,
             ElementType const* end)
        : m_current(begin),
          m_end(end) {
        Q_CHECK_PTR(begin);
        Q_CHECK_PTR(end);
    }

    operator bool() {
        return m_current != m_end;
    }
    ElementType const &operator*() {
        return m_current;
    }
    ElementType const* operator++() {
        return m_current++;
    }
};

} // namespace quantor
} // namespace q2d


#endif // ITERATOR_H
