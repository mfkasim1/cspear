#ifndef CSPEAR_ARRAY_ARRAY_LOGICAL_OP_H
#define CSPEAR_ARRAY_ARRAY_LOGICAL_OP_H

#include <type_traits>
#include <cspear/array/array.h>
#include <cspear/lib/init.h>
#include <cspear/tools/assert.h>

namespace csp {
  // logical operations
  // binary logical operations

  /**begin repeatop
  boolopname = ["operator&&", "operator||"];
  op = ["&&", "||"];
  */
  template <typename T, typename I>
  array<bool,I> array<T,I>::@boolopname@(const array<T,I>& a) {
    static_assert(std::is_same<T,bool>::value,
        "The logical operation can only be done with boolean array.");
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<bool,I> res = empty<bool,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] @op@ a.data_[i];
    }
    return res;
  }
  /**end repeatop**/

  // unary logical operations

  /**begin repeatop
  boolopname = ["operator!"];
  op = ["!"];
  */
  template <typename T, typename I>
  array<bool,I> array<T,I>::@boolopname@() {
    static_assert(std::is_same<T,bool>::value,
        "The logical operation can only be done with boolean array.");

    array<bool,I> res = empty<bool,I>(shape_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = @op@data_[i];
    }
    return res;
  }
  /**end repeatop**/


}

#endif
