#ifndef CSPEAR_ARRAY_ARRAY_REDUCE_H
#define CSPEAR_ARRAY_ARRAY_REDUCE_H

#include <initializer_list>
#include <limits>
#include <cspear/array/array.h>
#include <cspear/tools/assert.h>

namespace csp {
  /**begin repeatop
  opname = ["sum", "max", "min"];
  rinit_val = ["0",
               "std::numeric_limits<T>::lowest()",
               "std::numeric_limits<T>::max()"];
  op_r_data_i = ["r += data_[i]",
                 "r = std::max(r, data_[i])",
                 "r = std::min(r, data_[i])"];
  */
  template <typename T, typename I>
  T array<T,I>::@opname@() {
    T r = @rinit_val@;
    for (I i = 0; i < sz_; ++i) {
      @op_r_data_i@;
    }
    return r;
  }
  /**end repeatop**/

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
