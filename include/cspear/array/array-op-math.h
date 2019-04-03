#ifndef CSPEAR_ARRAY_ARRAY_OP_MATH_H
#define CSPEAR_ARRAY_ARRAY_OP_MATH_H

// implementation of the array operations

#include <cspear/array/array.h>
#include <cspear/array/op.h>
#include <cspear/array/ufuncs-math.h>

#define CSPEAR_MATH_ARRAY_OP_UNARY(op) \
template <typename T, typename I, template<typename> typename View> \
array<T,I,ContiguousView> array<T,I,View>::op() const { \
  return unary_op<array<T,I,ContiguousView>,ufunc::op<T> >(*this); \
} \
template <typename T, typename I, template<typename> typename View> \
array<T,I,View>& array<T,I,View>::op##_() const { \
  return inplace_unary_op<ufunc::op<T> >(*this); \
}

namespace csp {
  // inplace and non-inplace unary math operators
  CSPEAR_MATH_ARRAY_OP_UNARY(cos);
  CSPEAR_MATH_ARRAY_OP_UNARY(sin);
  CSPEAR_MATH_ARRAY_OP_UNARY(tan);
  CSPEAR_MATH_ARRAY_OP_UNARY(acos);
  CSPEAR_MATH_ARRAY_OP_UNARY(asin);
  CSPEAR_MATH_ARRAY_OP_UNARY(atan);
  CSPEAR_MATH_ARRAY_OP_UNARY(cosh);
  CSPEAR_MATH_ARRAY_OP_UNARY(sinh);
  CSPEAR_MATH_ARRAY_OP_UNARY(tanh);
  CSPEAR_MATH_ARRAY_OP_UNARY(exp);
  CSPEAR_MATH_ARRAY_OP_UNARY(log);
  CSPEAR_MATH_ARRAY_OP_UNARY(log10);
  CSPEAR_MATH_ARRAY_OP_UNARY(exp2);
  CSPEAR_MATH_ARRAY_OP_UNARY(expm1);
  CSPEAR_MATH_ARRAY_OP_UNARY(log1p);
  CSPEAR_MATH_ARRAY_OP_UNARY(log2);
  CSPEAR_MATH_ARRAY_OP_UNARY(sqrt);
  CSPEAR_MATH_ARRAY_OP_UNARY(cbrt);
  CSPEAR_MATH_ARRAY_OP_UNARY(erf);
  CSPEAR_MATH_ARRAY_OP_UNARY(erfc);
  CSPEAR_MATH_ARRAY_OP_UNARY(tgamma);
  CSPEAR_MATH_ARRAY_OP_UNARY(lgamma);
  CSPEAR_MATH_ARRAY_OP_UNARY(ceil);
  CSPEAR_MATH_ARRAY_OP_UNARY(floor);
  CSPEAR_MATH_ARRAY_OP_UNARY(round);
  CSPEAR_MATH_ARRAY_OP_UNARY(abs);
}

#endif
