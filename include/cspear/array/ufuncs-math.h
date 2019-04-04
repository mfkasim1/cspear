#ifndef CSPEAR_ARRAY_UFUNCS_MATH_H
#define CSPEAR_ARRAY_UFUNCS_MATH_H

#include <iostream>
#include <cmath>
#include <cspear/simd/vector.h>

/*
Universal functions for math operations.
Math operations are operations given in <cmath>.
This is csp::array wrapper for cmath operations.
*/

#define CSPEAR_MATH_UFUNC_UNARY(op) \
  template <typename T> \
  struct op { \
    static const bool has_simd = false; \
    static inline T unary(const T& a) { return std::op(a); } \
    static inline simd::Vector<T> simd_unary(const simd::Vector<T>& a) {} \
  };

#define CSPEAR_MATH_UFUNC_BINARY(op) \
  template <typename T> \
  struct op { \
    static const bool has_simd = false; \
    static inline T binary(const T& a, const T& b) { return std::op(a, b); } \
    static inline simd::Vector<T> simd_binary( \
        const simd::Vector<T>& a, const simd::Vector<T>& b) {} \
  };

namespace csp {
  namespace ufunc {
    // unary operations
    CSPEAR_MATH_UFUNC_UNARY(cos);
    CSPEAR_MATH_UFUNC_UNARY(sin);
    CSPEAR_MATH_UFUNC_UNARY(tan);
    CSPEAR_MATH_UFUNC_UNARY(acos);
    CSPEAR_MATH_UFUNC_UNARY(asin);
    CSPEAR_MATH_UFUNC_UNARY(atan);
    CSPEAR_MATH_UFUNC_BINARY(atan2);
    CSPEAR_MATH_UFUNC_UNARY(cosh);
    CSPEAR_MATH_UFUNC_UNARY(sinh);
    CSPEAR_MATH_UFUNC_UNARY(tanh);
    CSPEAR_MATH_UFUNC_UNARY(acosh);
    CSPEAR_MATH_UFUNC_UNARY(asinh);
    CSPEAR_MATH_UFUNC_UNARY(atanh);
    CSPEAR_MATH_UFUNC_UNARY(exp);
    CSPEAR_MATH_UFUNC_UNARY(log);
    CSPEAR_MATH_UFUNC_UNARY(log10);
    CSPEAR_MATH_UFUNC_UNARY(exp2);
    CSPEAR_MATH_UFUNC_UNARY(expm1);
    CSPEAR_MATH_UFUNC_UNARY(log1p);
    CSPEAR_MATH_UFUNC_UNARY(log2);
    CSPEAR_MATH_UFUNC_BINARY(pow);
    CSPEAR_MATH_UFUNC_UNARY(sqrt);
    CSPEAR_MATH_UFUNC_UNARY(cbrt);
    CSPEAR_MATH_UFUNC_BINARY(hypot);
    CSPEAR_MATH_UFUNC_UNARY(erf);
    CSPEAR_MATH_UFUNC_UNARY(erfc);
    CSPEAR_MATH_UFUNC_UNARY(tgamma);
    CSPEAR_MATH_UFUNC_UNARY(lgamma);
    CSPEAR_MATH_UFUNC_UNARY(ceil);
    CSPEAR_MATH_UFUNC_UNARY(trunc);
    CSPEAR_MATH_UFUNC_UNARY(floor);
    CSPEAR_MATH_UFUNC_UNARY(round);
    CSPEAR_MATH_UFUNC_UNARY(abs);
  }
}

#endif
