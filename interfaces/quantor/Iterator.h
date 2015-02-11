#ifndef Q2D_QUANTOR_ITERATOR_H
#define Q2D_QUANTOR_ITERATOR_H

namespace q2d {
namespace quantor {

/**
 * Java-style iterator with self-contained range semantics.
 * Templated instances can be created from arbitrary C++
 * forward iterators specifying the beginning and the end
 * of a range.
 *
 * @author Thomas B. Preußer <thomas.preusser@utexas.edu>
 */
template<typename T>
class Iterator {
private:
  T        m_cur;
  T const  m_end;

public:
  Iterator(T beg, T end) : m_cur(beg), m_end(end) {}

  operator bool() const {
    return m_cur != m_end;
  }
  auto operator*() -> decltype(*m_cur) {
    return *m_cur;
  }
  auto operator->() -> decltype(&*m_cur) {
    return &*m_cur;
  }
  Iterator<T> operator++() {
    m_cur++;
    return *this;
  }
  Iterator<T> operator++(int) {
    Iterator<T> const  old = *this;
    m_cur++;
    return  old;
  }
};

} // namespace quantor
} // namespace q2d

#endif // ITERATOR_H
