#ifndef CSPEAR_CORE_MATH_H
#define CSPEAR_CORE_MATH_H

#include <cmath>
#include <cspear/core/array.h>
#include <cspear/lib/init.h>

namespace csp {
  // properties of the array

  /**begin repeat
  mathfn = ["sin", "cos", "tan", "asin", "acos", "atan", "atan2",
            "sinh", "cosh", "tanh", "asinh", "acosh", "atanh",
            "exp", "log", "log10", "exp2", "expm1", "log1p", "log2",
            "sqrt", "cbrt",
            "erf", "erfc", "tgamma", "lgamma",
            "ceil", "floor", "round", "fabs"];
  */
  template <typename T, typename I>
  array<T,I> array<T,I>::@mathfn@() const {
    array<T,I> res = empty<T,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res[i] = std::@mathfn@(data_[i]);
    }
    return res;
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::@mathfn@_() {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = std::@mathfn@(data_[i]);
    }
    return *this;
  }
  /**end repeat**/

  /**begin repeat
  mathfn = ["sqr", "cube"];
  op_d = ["d*d", "d*d*d"];
  */
  template <typename T, typename I>
  array<T,I> array<T,I>::@mathfn@() const {
    array<T,I> res = empty<T,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      auto& d = data_[i];
      res[i] = @op_d@;
    }
    return res;
  }

  template <typename T, typename I>
  array<T,I>& array<T,I>::@mathfn@_() {
    for (I i = 0; i < sz_; ++i) {
      auto& d = data_[i];
      data_[i] = @op_d@;
    }
    return *this;
  }
  /**end repeat**/
}

#endif
