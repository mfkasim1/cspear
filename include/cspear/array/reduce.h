#ifndef CSPEAR_ARRAY_REDUCE_H
#define CSPEAR_ARRAY_REDUCE_H

#include <stdexcept>
#include <algorithm>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>
#include <cspear/iterators/reduce-iterator.h>

namespace csp {
  template <typename TR, typename InpType, typename F>
  TR reduce_all(F&& f, const InpType& arr, TR initval) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;

    TR res = initval;

    // performing the iteration
    auto it1 = EWiseIterator<T,I,View>((T*)arr.data(), arr.view());
    for (; it1; ++it1) {
      f(res, *it1);
    }
    return res;
  }

  template <typename ResType, typename TR, typename InpType, typename IAx,
            typename F>
  ResType reduce_axis(F&& f, const InpType& arr, const IAx& ax, TR initval) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;

    // get the shape of the result
    std::vector<IAx> axis = {ax};
    auto rshape = reduce_output_shape(axis, arr.shape());
    ResType res = ResType::full(rshape, initval);

    // performing the iteration
    auto it1 = ReduceIterator<T,I,View>(axis,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it1; ++it1) {
      f(it1.result(), it1.first());
    }
    return res;
  }

  template <typename ResType, typename TR, typename InpType, typename AxType,
            typename F>
  ResType reduce_axes(F&& f, const InpType& arr, const AxType& axes, TR initval) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;

    // order ax
    AxType ax = axes;
    std::sort(ax.begin(), ax.end());

    // get the shape of the result
    auto rshape = reduce_output_shape(ax, arr.shape());
    ResType res = ResType::full(rshape, initval);

    // performing the iteration
    auto it1 = ReduceIterator<T,I,View>(ax,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it1; ++it1) {
      f(it1.result(), it1.first());
    }
    return res;
  }
}

#endif
