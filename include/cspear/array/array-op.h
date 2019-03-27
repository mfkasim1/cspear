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
    return unary_op<array<T,I,ContiguousView>,ufunc::neg<T> >(*this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator+(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::add<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator-(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::sub<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator*(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::mult<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator/(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::div<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::reciprocal(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::reciprocal<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_lb(T lb) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::clip_lb<T> >(
      *this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_ub(T ub) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView>, ufunc::clip_ub<T> >(
      *this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip(T lb, T ub) {
    return clip_lb(lb).clip_ub(ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator!() {
    return unary_op< array<bool,I,ContiguousView>,ufunc::logical_not<T> >(*this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::gt<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::gteq<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::lt<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::lteq<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::eq<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator!=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::neq<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::logical_and<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView>, ufunc::logical_or<T> >(
      *this, a);
  }


  // inplace unary operators and binary operators with a value
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator=(T a) {
    return ewise_inplace_binary_op_with_val< ufunc::assign<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator+=(T a) {
    return ewise_inplace_binary_op_with_val< ufunc::add<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator-=(T a) {
    return ewise_inplace_binary_op_with_val<ufunc::sub<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator*=(T a) {
    return ewise_inplace_binary_op_with_val<ufunc::mult<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator/=(T a) {
    return ewise_inplace_binary_op_with_val<ufunc::div<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reciprocal_(T a) {
    return ewise_inplace_binary_op_with_val<ufunc::reciprocal<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_lb_(T lb) {
    return ewise_inplace_binary_op_with_val<ufunc::clip_lb<T> >(*this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_ub_(T ub) {
    return ewise_inplace_binary_op_with_val<ufunc::clip_ub<T> >(*this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_(T lb, T ub) {
    return clip_lb_(lb).clip_ub_(ub);
  }

  // binary operators (non inplace)
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator+(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView>,ufunc::add<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator-(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView>,ufunc::sub<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator*(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView>,ufunc::mult<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator/(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView>,ufunc::div<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::gt<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::gteq<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::lt<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::lteq<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::eq<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator!=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::neq<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>, ufunc::logical_and<T> >(
      *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView>,ufunc::logical_or<T> >(
      *this, a);
  }


  // inplace binary operators
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::assign_(const array<T,I,View2>& a) {
    return inplace_binary_op<ufunc::assign<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator+=(const array<T,I,View2>& a) {
    return inplace_binary_op<ufunc::add<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator-=(const array<T,I,View2>& a) {
    return inplace_binary_op<ufunc::sub<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator*=(const array<T,I,View2>& a) {
    return inplace_binary_op<ufunc::mult<T> >(*this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator/=(const array<T,I,View2>& a) {
    return inplace_binary_op<ufunc::div<T> >(*this, a);
  }
}

#endif
