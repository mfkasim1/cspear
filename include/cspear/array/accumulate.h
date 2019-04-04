#ifndef CSPEAR_ARRAY_ACCUMULATE_H
#define CSPEAR_ARRAY_ACCUMULATE_H

#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>
#include <cspear/iterators/accumulate-iterator.h>

namespace csp {
  template <typename ResType, typename f, typename InpType>
  ResType accumulate_all(const InpType& arr) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    if (arr.size() == 0) {
      return {};
    }

    ResType res = ResType::empty(arr.shape());
    TR r = f::identity;

    // performing the iteration
    auto it1 = EWiseIterator<T,I,View>((T*)arr.data(), arr.view());
    auto itr = EWiseIterator<TR,IR,ViewR>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++itr) {
      r = f::binary(r, *it1);
      *itr = r;
    }
    return res;
  }

  template <typename ResType, typename f, typename InpType, typename IAx>
  ResType accumulate_axis(const InpType& arr, const IAx& ax) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    if (arr.size() == 0) {
      return {};
    }

    // check the axis
    _cspear_assert(((ax < arr.ndim()) && (ax >= 0)), "Out-of-the bound index");
    ResType res = ResType::empty(arr.shape());

    // performing the iteration
    auto it = AccumulateIterator<T,I,View>(ax, f::identity,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it; ++it) {
      it.result() = f::binary(it.prev(), it.first());
    }
    return res;
  }
}

#endif
