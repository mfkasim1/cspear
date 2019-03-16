#ifndef CSPEAR_CORE_ARRAY_MISC_H
#define CSPEAR_CORE_ARRAY_MISC_H

#include <cspear/core/array.h>
#include <cspear/lib/init.h>
#include <cspear/tools/assert.h>

namespace csp {

  template <typename T, typename I>
  array<T,I> array<T,I>::clip_lb(T lb) const {
    array<T,I> res = empty<T,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res[i] = (data_[i] < lb) ? lb : data_[i];
    }
    return res;
  }

  template <typename T, typename I>
  array<T,I> array<T,I>::clip_ub(T ub) const {
    array<T,I> res = empty<T,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res[i] = (data_[i] > ub) ? ub : data_[i];
    }
    return res;
  }

  template <typename T, typename I>
  array<T,I> array<T,I>::clip(T lb, T ub) const {
    array<T,I> res = empty<T,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res[i] = (data_[i] > ub) ? ub :
              ((data_[i] < lb) ? lb : data_[i]);
    }
    return res;
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::clip_lb_(T lb) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = (data_[i] < lb) ? lb : data_[i];
    }
    return *this;
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::clip_ub_(T ub) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = (data_[i] > ub) ? ub : data_[i];
    }
    return *this;
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::clip_(T lb, T ub) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = (data_[i] > ub) ? ub :
                ((data_[i] < lb) ? lb : data_[i]);
    }
    return *this;
  }
}

#endif
