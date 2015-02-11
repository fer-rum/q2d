#ifndef ITERATOR_H
#define ITERATOR_H

#include <QtDebug>

namespace q2d {
namespace quantor {

/**
 *  This class has been introduced for TBP-code compatibility.
 */
template<typename ElementType>
class Iterator {
private:
    ElementType const *       m_current;
    ElementType const *const  m_end;

public:

    Iterator(ElementType const* begin,
             ElementType const* end)
        : m_current(begin),
          m_end(end) {
        Q_CHECK_PTR(begin);
        Q_CHECK_PTR(end);
    }

    operator bool() const {
        return m_current != m_end;
    }
    ElementType const &operator*() {
        return *m_current;
    }
    Iterator<ElementType> operator++() {
	Iterator<ElementType> const  old = *this;
	m_current++;
        return  old;
    }
};

} // namespace quantor
} // namespace q2d

#endif // ITERATOR_H
