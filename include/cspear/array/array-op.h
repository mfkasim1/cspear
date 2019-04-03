#ifndef CSPEAR_ARRAY_ARRAY_OP_H
#define CSPEAR_ARRAY_ARRAY_OP_H

// implementation of the array operations

#include <cspear/array/array.h>
#include <cspear/array/op.h>
#include <cspear/array/ufuncs.h>

namespace csp {
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip(T lb, T ub) const {
    return clip_lb(lb).clip_ub(ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_(T lb, T ub) {
    return clip_lb_(lb).clip_ub_(ub);
  }

}

#endif
