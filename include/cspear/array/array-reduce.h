#ifndef CSPEAR_ARRAY_ARRAY_REDUCE_H
#define CSPEAR_ARRAY_ARRAY_REDUCE_H

#include <initializer_list>
#include <limits>
#include <cspear/array/array.h>
#include <cspear/array/reduce.h>
#include <cspear/array/ufuncs.h>
#include <cspear/tools/assert.h>

namespace csp {
  // reduce all elements
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::sum() const {
    return reduce_all<ufunc::add<T>,false >(
      *this, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::max() const {
    return reduce_all<ufunc::max<T>,true >(
      *this, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::min() const {
    return reduce_all<ufunc::min<T>,true >(
      *this, std::numeric_limits<T>::max()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::all() const {
    return reduce_all<ufunc::logical_and<T>,false >(
      *this, true
    );
  }
  template <typename T, typename I, template<typename> typename View>
  T array<T,I,View>::any() const {
    return reduce_all<ufunc::logical_or<T>,false >(
      *this, false
    );
  }

  // reduce an axis
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::sum(I ax) const {
    return reduce_axis<array<T,I,ContiguousView>,ufunc::add<T>,false >(
      *this, ax, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::max(I ax) const {
    return reduce_axis<array<T,I,ContiguousView>,ufunc::max<T>,true >(
      *this, ax, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::min(I ax) const {
    return reduce_axis<array<T,I,ContiguousView>,ufunc::min<T>,true >(
      *this, ax, std::numeric_limits<T>::max()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::all(I ax) const {
    return reduce_axis<array<T,I,ContiguousView>,ufunc::logical_and<T>,false >(
      *this, ax, true
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::any(I ax) const {
    return reduce_axis<array<T,I,ContiguousView>,ufunc::logical_or<T>,false >(
      *this, ax, false
    );
  }

  // reduce an axes
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::sum(const std::vector<I>& ax) const {
    return reduce_axes<array<T,I,ContiguousView>,ufunc::add<T>,false >(
      *this, ax, (T)0
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::max(const std::vector<I>& ax) const {
    return reduce_axes<array<T,I,ContiguousView>,ufunc::max<T>,true >(
      *this, ax, std::numeric_limits<T>::lowest()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::min(const std::vector<I>& ax) const {
    return reduce_axes<array<T,I,ContiguousView>,ufunc::min<T>,true >(
      *this, ax, std::numeric_limits<T>::max()
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::all(const std::vector<I>& ax) const {
    return reduce_axes<array<T,I,ContiguousView>,ufunc::logical_and<T>,false >(
      *this, ax, true
    );
  }
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::any(const std::vector<I>& ax) const {
    return reduce_axes<array<T,I,ContiguousView>,ufunc::logical_or<T>,false >(
      *this, ax, false
    );
  }
}

#endif
