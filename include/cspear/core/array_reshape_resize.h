#ifndef CSPEAR_CORE_ARRAY_RESHAPE_RESIZE_H
#define CSPEAR_CORE_ARRAY_RESHAPE_RESIZE_H

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <initializer_list>
#include <cspear/core/array.h>
#include <cspear/core/utils.h>
#include <cspear/core/assert.h>

namespace csp {
  template <typename T, typename I>
  array<T,I>& array<T,I>::resize(I sz) {
    if (sz_ == sz) {
      return *this;
    }
    else {
      sz_ = sz;
      _realloc();
      shape_ = {sz_}; // make it a one-dimensional array
      return *this;
    }
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::reshape(std::initializer_list<I> shape) {
    I sz = _calculate_size(shape);
    assert(sz == sz_);
    shape_ = shape;
    return *this;
  }
}

#endif
