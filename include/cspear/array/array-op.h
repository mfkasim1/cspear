#ifndef CSPEAR_ARRAY_ARRAY_OP_H
#define CSPEAR_ARRAY_ARRAY_OP_H

// implementation of the array operations

#include <cspear/array/array.h>
#include <cspear/array/op.h>
#include <cspear/array/ufuncs.h>

namespace csp {
  // non inplace unary operators and binary with a value
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator-() {
    return unary_op< array<T,I,ContiguousView> >(ufunc::neg<T>::unary, *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator+(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::add<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator-(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::sub<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator*(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::mult<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator/(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::div<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::reciprocal(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::reciprocal<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_lb(T lb) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::clip_lb<T>::binary, *this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_ub(T ub) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      ufunc::clip_ub<T>::binary, *this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip(T lb, T ub) {
    return unary_op< array<T,I,ContiguousView> >(
      [&](T& b) {return (b < lb) ? lb : ((b > ub) ? ub : b);},
      *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator!() {
    return unary_op< array<bool,I,ContiguousView> >(
      ufunc::logical_not<T>::unary, *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::gt<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::gteq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::lt<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::lteq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::eq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator!=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::neq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::logical_and<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      ufunc::logical_or<T>::binary, *this, a);
  }


  // inplace unary operators and binary operators with a value
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator+=(T a) {
    return ewise_inplace_binary_op_with_val(
      ufunc::add<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator-=(T a) {
    return ewise_inplace_binary_op_with_val(
      ufunc::sub<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator*=(T a) {
    return ewise_inplace_binary_op_with_val(
      ufunc::mult<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator/=(T a) {
    return ewise_inplace_binary_op_with_val(
      ufunc::div<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reciprocal_(T a) {
    return ewise_inplace_binary_op_with_val(
      ufunc::reciprocal<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_lb_(T lb) {
    return ewise_inplace_binary_op_with_val(
      ufunc::clip_lb<T>::binary, *this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_ub_(T ub) {
    return ewise_inplace_binary_op_with_val(
      ufunc::clip_ub<T>::binary, *this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_(T lb, T ub) {
    return inplace_unary_op(
      [&](T& b) {
        b = (b < lb) ? lb : (b > ub ? ub : b);
      }, *this);
  }

  // binary operators (non inplace)
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator+(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      ufunc::add<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator-(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      ufunc::sub<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator*(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      ufunc::mult<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator/(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      ufunc::div<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::gt<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::gteq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::lt<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::lteq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::eq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator!=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::neq<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::logical_and<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      ufunc::logical_or<T>::binary, *this, a);
  }


  // inplace binary operators
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::assign_(const array<T,I,View2>& a) {
    return inplace_binary_op(ufunc::assign<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator+=(const array<T,I,View2>& a) {
    return inplace_binary_op(ufunc::add<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator-=(const array<T,I,View2>& a) {
    return inplace_binary_op(ufunc::sub<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator*=(const array<T,I,View2>& a) {
    return inplace_binary_op(ufunc::mult<T>::binary, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator/=(const array<T,I,View2>& a) {
    return inplace_binary_op(ufunc::div<T>::binary, *this, a);
  }
}

#endif
