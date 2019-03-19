#ifndef CSPEAR_ARRAY_ARRAY_OP_H
#define CSPEAR_ARRAY_ARRAY_OP_H

#include <cspear/array/array.h>
#include <cspear/tools/assert.h>

namespace csp {
  // unary operations
  template <typename T, typename I>
  array<T,I> array<T,I>::operator-() {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = -data_[i];
    }
    return res;
  }

  // binary operations

  /**begin repeatop
  opname = ["operator+", "operator-", "operator*", "operator/"];
  op = ["+", "-", "*", "/"];
  */
  template <typename T, typename I>
  array<T,I> array<T,I>::@opname@(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] @op@ a.data_[i];
    }
    return res;
  }
  /**end repeatop**/

  /**begin repeatop
  opname = ["operator+", "operator-", "operator*", "operator/"];
  op = ["+", "-", "*", "/"];
  */
  template <typename T, typename I>
  array<T,I> array<T,I>::@opname@(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] @op@ a;
    }
    return res;
  }
  /**end repeatop**/

  template <typename T, typename I>
  array<T,I> array<T,I>::rdiv(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = a / data_[i];
    }
    return res;
  }

  // binary operations (inplace)

  /**begin repeatop
  opname = ["operator+=", "operator-=", "operator*=", "operator/="];
  op = ["+", "-", "*", "/"];
  */
  template <typename T, typename I>
  array<T,I>& array<T,I>::@opname@(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    for (I i = 0; i < sz_; ++i) {
      data_[i] @op@= a.data_[i];
    }
    return *this;
  }
  /**end repeatop**/

  /**begin repeatop
  opname = ["operator+=", "operator-=", "operator*=", "operator/="];
  op = ["+", "-", "*", "/"];
  */
  template <typename T, typename I>
  array<T,I>& array<T,I>::@opname@(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] @op@= a;
    }
    return *this;
  }
  /**end repeatop**/

  template <typename T, typename I>
  array<T,I>& array<T,I>::rdiv_(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = a / data_[i];
    }
    return *this;
  }
}

#endif
