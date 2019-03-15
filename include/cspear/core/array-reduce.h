#ifndef CSPEAR_CORE_ARRAY_REDUCE_H
#define CSPEAR_CORE_ARRAY_REDUCE_H

#include <initializer_list>
#include <cspear/core/array.h>
#include <cspear/tools/assert.h>

namespace csp {
  template <typename T, typename I>
  T sum() {
    T r = 0;
    for (I i = 0; i < sz_; ++i) {
      r += data_[i];
    }
    return r;
  }

  template <typename T, typename I>
  array<T,I> sum(I axis) {
    // ???
    array<T,I> res;
    return res;
  }

  template <typename T, typename I>
  array<T,I> sum(std::initializer_list<T> axes) {
    // ???
    array<T,I> res;
    return res;
  }
}

#endif
