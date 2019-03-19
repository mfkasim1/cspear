#ifndef CSPEAR_LIB_INIT_H
#define CSPEAR_LIB_INIT_H

#include <vector>
#include <initializer_list>
#include <cspear/array/array.h>
#include <cspear/tools/misc.h>

namespace csp {
  /**begin repeat
  vectype = ["const std::vector<I>&", "std::initializer_list<I>"];
  */
  template <typename T, typename I=tools::Int>
  array<T,I> empty(@vectype@ shape) {
    array<T,I> res;
    I sz = tools::_prod_init_list(shape);
    res.resize(sz).reshape(shape);
    return res;
  }

  template <typename T, typename I=tools::Int>
  array<T,I> zeros(@vectype@ shape) {
    array<T,I> res = empty(shape);
    std::memset(res.data(), 0, res.size()*sizeof(T));
    return res;
  }

  template <typename T, typename I=tools::Int>
  array<T,I> ones(@vectype@ shape) {
    array<T,I> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)1);
    return res;
  }

  template <typename T, typename I=tools::Int>
  array<T,I> full(@vectype@ shape, T value) {
    array<T,I> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)value);
    return res;
  }
  /**end repeat**/

  template <typename T, typename I=tools::Int>
  array<T,I> arange(T begin, T end, T range) {
    array<T,I> res;
    I sz = (end - begin) / range;
    res.resize(sz);
    I ir = 0;
    for (T i = begin; i < end; i+=range) {
      res[ir++] = i;
    }
    return res;
  }

  template <typename T, typename I=tools::Int>
  array<T,I> arange(T end) {
    return arange((T)0, end, (T)1);
  }

  template <typename T, typename I=tools::Int>
  array<T,I> arange(T begin, T end) {
    return arange(begin, end, (T)1);
  }

  template <typename T, typename I=tools::Int>
  array<T,I> linspace(T begin, T end, I n) {
    array<T,I> res;
    res.resize(n);
    T di = n > 1 ? (end - begin) / (n - 1) : 1;
    T i = begin;
    for (I ir = 0; ir < n; ++ir) {
      res[ir] = i;
      i += di;
    }
    return res;
  }
}
#endif
