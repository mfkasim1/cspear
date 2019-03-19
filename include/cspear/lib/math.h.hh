#ifndef CSPEAR_LIB_MATH_H
#define CSPEAR_LIB_MATH_H

#include <cmath>
#include <cspear/array/array.h>
#include <cspear/array/array-math.h>
#include <cspear/lib/init.h>

namespace csp {
  // works on array

  /**begin repeat
  mathfn = ["sin", "cos", "tan", "asin", "acos", "atan", "atan2",
            "sinh", "cosh", "tanh", "asinh", "acosh", "atanh",
            "exp", "log", "log10", "exp2", "expm1", "log1p", "log2",
            "sqrt", "cbrt", "sqr", "cube",
            "erf", "erfc", "tgamma", "lgamma",
            "ceil", "floor", "round", "fabs"];
  */
  template <typename T, typename I>
  array<T,I> @mathfn@(const array<T,I>& a) {
    return a.@mathfn@();
  }

  template <typename T, typename I>
  array<T,I>& @mathfn@_(array<T,I>& a) {
    return a.@mathfn@_();
  }
  /**end repeat**/

  // works on a single number
  /**begin repeat
  mathfn = ["sin", "cos", "tan", "asin", "acos", "atan", "atan2",
            "sinh", "cosh", "tanh", "asinh", "acosh", "atanh",
            "exp", "log", "log10", "exp2", "expm1", "log1p", "log2",
            "sqrt", "cbrt",
            "erf", "erfc", "tgamma", "lgamma",
            "ceil", "floor", "round", "fabs"];
  */
  template <typename T>
  inline T @mathfn@(T a) {
    return std::@mathfn@(a);
  }
  /**end repeat**/
  /**begin repeat
  mathfn = ["sqr", "cube"];
  op_a = ["a*a", "a*a*a"];
  */
  template <typename T>
  inline T @mathfn@(T a) {
    return @op_a@;
  }
  /**end repeat**/

}

#endif
