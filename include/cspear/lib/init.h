#ifndef CSPEAR_LIB_INIT_H
#define CSPEAR_LIB_INIT_H

#include <vector>
#include <initializer_list>
#include <cspear/array/array.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/tools/misc.h>

namespace csp {
  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> empty(const std::vector<I>& shape) {
    return array<T,I,ContiguousView>::empty(shape);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> zeros(const std::vector<I>& shape) {
    return array<T,I,ContiguousView>::zeros(shape);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> ones(const std::vector<I>& shape) {
    return array<T,I,ContiguousView>::ones(shape);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> full(const std::vector<I>& shape, T value) {
    return array<T,I,ContiguousView>::full(shape, value);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> arange(T begin, T end, T range) {
    return array<T,I,ContiguousView>::arange(begin, end, range);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> arange(T end) {
    return array<T,I,ContiguousView>::arange(end);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> arange(T begin, T end) {
    return array<T,I,ContiguousView>::arange(begin, end);
  }

  template <typename T=tools::Real, typename I=tools::Int>
  inline array<T,I,ContiguousView> linspace(T begin, T end, I n) {
    return array<T,I,ContiguousView>::linspace(begin, end, n);
  }
}
#endif
