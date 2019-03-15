#ifndef CSPEAR_CORE_ARRAY_CONSTRUCTORS_DESTRUCTOR_H
#define CSPEAR_CORE_ARRAY_CONSTRUCTORS_DESTRUCTOR_H

#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <cspear/core/array.h>
#include <cspear/tools/misc.h>
#include <cspear/core/utils.h>
#include <cspear/core/assert.h>

namespace csp {
  template <typename T, typename I>
  array<T,I>::array() {
    sz_ = 0;
    allocated_ = false;
  }

  template <typename T, typename I>
  array<T,I>::array(std::initializer_list<T> elmts) {
    // copy the data
    sz_ = elmts.size();
    _realloc();
    std::copy(elmts.begin(), elmts.end(), data_);

    // set the shape
    shape_ = {sz_};
  }

  template <typename T, typename I>
  array<T,I>::array(const T* a, I sz) : array(sz) {
    // copy the data
    std::copy(a, a+sz, data_);
  }

  template <typename T, typename I>
  array<T,I>::array(const T* a, std::initializer_list<I> shape) {
    // get the size
    sz_ = tools::_prod_init_list(shape);

    // copy the data
    _realloc();
    std::copy(a, a+sz_, data_);

    // set the shape
    shape_ = shape;
  }

  template <typename T, typename I>
  array<T,I>::array(const array<T,I>& a) {
    // copy the data
    sz_ = a.size();
    _realloc();
    std::copy(a.data(), a.data()+sz_, data_);

    // copy the shape as well
    shape_ = a.shape();
  }

  template <typename T, typename I>
  array<T,I>::~array() {
    if (allocated_) {
      std::free(data_);
    }
  }

  template <typename T, typename I>
  void array<T,I>::_realloc() {
    if (allocated_) std::free(data_);
    data_ = (T*) std::malloc(sz_*sizeof(*data_));
    assert_cpu(data_, "CPU memory allocation failed.");
    allocated_ = true;
  }
}

#endif
