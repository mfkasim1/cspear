#ifndef CSPEAR_ARRAY_ARRAY_CMP_OP_H
#define CSPEAR_ARRAY_ARRAY_CMP_OP_H

#include <cspear/array/array.h>
#include <cspear/lib/init.h>
#include <cspear/tools/assert.h>

namespace csp {
  // binary comparison operations

  /**begin repeatop
  cmpopname = ["operator>", "operator<", "operator>=", "operator<=",
                "operator==", "operator!="];
  op = [">", "<", ">=", "<=", "==", "!="];
  */
  template <typename T, typename I>
  array<bool,I> array<T,I>::@cmpopname@(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<bool,I> res = empty<bool,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] @op@ a.data_[i];
    }
    return res;
  }
  /**end repeatop**/

  /**begin repeatop
  cmpopname = ["operator>", "operator<", "operator>=", "operator<=",
                "operator==", "operator!="];
  op = [">", "<", ">=", "<=", "==", "!="];
  */
  template <typename T, typename I>
  array<bool,I> array<T,I>::@cmpopname@(T a) {
    array<bool,I> res = empty<bool,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] @op@ a;
    }
    return res;
  }
  /**end repeatop**/
}

#endif
