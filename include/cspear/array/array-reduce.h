#ifndef CSPEAR_ARRAY_ARRAY_REDUCE_H
#define CSPEAR_ARRAY_ARRAY_REDUCE_H

#include <initializer_list>
#include <limits>
#include <cspear/array/array.h>
#include <cspear/array/reduce.h>
#include <cspear/tools/assert.h>

namespace csp {
  // reduce all elements
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::sum() {
    return reduce_all(
      [](T& r, const T& elmt) { r += elmt; },
      *this, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::max() {
    return reduce_all(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::min() {
    return reduce_all(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, std::numeric_limits<T>::max()
    );
  }

  // reduce an axis
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::sum(I ax) {
    return reduce_axis<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r += elmt; },
      *this, ax, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::max(I ax) {
    return reduce_axis<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, ax, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::min(I ax) {
    return reduce_axis<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, ax, std::numeric_limits<T>::max()
    );
  }

  // reduce an axes
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::sum(const std::vector<I>& ax) {
    return reduce_axes<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r += elmt; },
      *this, ax, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::max(const std::vector<I>& ax) {
    return reduce_axes<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, ax, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::min(const std::vector<I>& ax) {
    return reduce_axes<array<T,I,ContiguousView> >(
      [](T& r, const T& elmt) { r = elmt > r ? elmt : r; },
      *this, ax, std::numeric_limits<T>::max()
    );
  }
}

#endif
