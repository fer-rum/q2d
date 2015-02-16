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
template<typename T = void>
class Iterator {
private:
  T        m_cur;
  T const  m_end;

public:
  Iterator(T beg, T end) : m_cur(beg), m_end(end) {}
  ~Iterator() {}

public:
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

template<>
class Iterator<void> {
public:
template<typename T>
static Iterator<T> span(T beg, T end) {
  return  Iterator<T>(beg, end);
}
template<typename T>
static auto over(T cont) -> Iterator<decltype(cont.begin())> {
  return  span(cont.begin(), cont.end());
}
};
} // namespace quantor
} // namespace q2d

#endif // ITERATOR_H
