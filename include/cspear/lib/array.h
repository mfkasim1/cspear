#ifndef CSPEAR_LIB_ARRAY_H
#define CSPEAR_LIB_ARRAY_H

#include <cspear/array/array.h>

/*
This file is to expose the array function to csp:: namespace.
*/

#define CSPEAR_EXPOSE_ARRAY_FUNC(funcname)                                      \
  template <typename ArrType, typename View=typename ArrType::ViewType,         \
            typename ... Args>                                                  \
  auto inline funcname(ArrType& arr, Args... args) {                            \
    return arr.funcname(args...);                                               \
  }                                                                             \
  template <typename ArrType, typename View=typename ArrType::ViewType,         \
            typename ... Args>                                                  \
  auto inline funcname(const ArrType& arr, Args... args) {                      \
    return arr.funcname(args...);                                               \
  }

#define CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(funcname)                         \
        CSPEAR_EXPOSE_ARRAY_FUNC(funcname)                                      \
        CSPEAR_EXPOSE_ARRAY_FUNC(funcname##_)

namespace csp {
  // reduce
  CSPEAR_EXPOSE_ARRAY_FUNC(sum);
  CSPEAR_EXPOSE_ARRAY_FUNC(prod);
  CSPEAR_EXPOSE_ARRAY_FUNC(max);
  CSPEAR_EXPOSE_ARRAY_FUNC(min);
  CSPEAR_EXPOSE_ARRAY_FUNC(all);
  CSPEAR_EXPOSE_ARRAY_FUNC(any);
  CSPEAR_EXPOSE_ARRAY_FUNC(argmax);
  CSPEAR_EXPOSE_ARRAY_FUNC(argmin);

  // accumulate
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(cumsum);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(cumprod);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(cummax);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(cummin);

  // arithmetic
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(neg);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(add);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(sub);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(mult);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(div);
  CSPEAR_EXPOSE_ARRAY_FUNC(reciprocal);

  // comparison
  CSPEAR_EXPOSE_ARRAY_FUNC(gt);
  CSPEAR_EXPOSE_ARRAY_FUNC(lt);
  CSPEAR_EXPOSE_ARRAY_FUNC(gteq);
  CSPEAR_EXPOSE_ARRAY_FUNC(lteq);
  CSPEAR_EXPOSE_ARRAY_FUNC(eq);
  CSPEAR_EXPOSE_ARRAY_FUNC(neq);

  // logical operator
  CSPEAR_EXPOSE_ARRAY_FUNC(logical_not);
  CSPEAR_EXPOSE_ARRAY_FUNC(logical_and);
  CSPEAR_EXPOSE_ARRAY_FUNC(logical_or);

  // clip operation
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(clip);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(maximum);
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(minimum);

  // fill / assignment
  CSPEAR_EXPOSE_ARRAY_FUNC_WITH_INPLACE(fill);
}

#endif
