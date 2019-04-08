#ifndef CSPEAR_LIB_GRAD_H
#define CSPEAR_LIB_GRAD_H

#include <algorithm>
#include <cspear/array/array.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/slice.h>
#include <cspear/tools/assert.h>

namespace csp {
  template <typename ArrType, typename I>
  auto diff(const ArrType& arr, I ax, I n=1) ->
       // return type
       array<typename ArrType::DataType,
             typename ArrType::IndexType,
             ContiguousView> {

    if (n > 1) {
      return diff(diff(arr, ax, 1), ax, n-1);
    }

    // check the input
    const auto& shape = arr.shape();
    I ndim = arr.ndim();
    _cspear_assert((ax < ndim) && (ax >= 0), "Out-of-bounds axis in diff "
                                             "function.");
    _cspear_assert(shape[ax] > n, "The number of rows in the given axis is "
                                  "not enough for diff operation.");

    if (ax == 0) {
      return arr.at(1,shape[ax]) - arr.at(0,shape[ax]-1);
    }
    else {
      // get the slicing index
      std::vector< Slice<I> > lslice(ndim, csp::whole());
      std::vector< Slice<I> > rslice = lslice;
      lslice[ax] = Slice<I>({0,shape[ax]-1});
      rslice[ax] = csp::from(1);

      return arr.slice(rslice) - arr.slice(lslice);
    }
  }
}

#endif
