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
  void accumulate_all_general(ResType& res, const InpType& arr) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    TR r = f::identity;

    // performing the iteration
    auto it1 = arr.iterator();
    auto itr = res.iterator();
    for (; it1; ++it1, ++itr) {
      r = f::binary(r, *it1);
      *itr = r;
    }
  }

  template <typename ResType, typename f, typename InpType, typename IAx>
  void accumulate_axis_general(ResType& res, const InpType& arr, const IAx& ax) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    // check the axis
    _cspear_assert(((ax < arr.ndim()) && (ax >= 0)), "Out-of-the bound index");

    // performing the iteration
    auto it = AccumulateIterator(ax, f::identity,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it; ++it) {
      it.result() = f::binary(it.prev(), it.first());
    }
  }

  template <typename ResType, typename f, typename InpType>
  inline ResType accumulate_all(const InpType& arr) {
    if (arr.size() == 0) {
      return {};
    }
    ResType res = ResType::empty(arr.shape());
    accumulate_all_general<ResType,f,InpType>(res, arr);
    return res;
  }

  template <typename ResType, typename f, typename InpType, typename IAx>
  inline ResType accumulate_axis(const InpType& arr, const IAx& ax) {
    if (arr.size() == 0) {
      return {};
    }
    ResType res = ResType::empty(arr.shape());
    accumulate_axis_general<ResType,f,InpType,IAx>(res, arr, ax);
    return res;
  }

  template <typename f, typename InpType>
  inline InpType& accumulate_all_inplace(InpType& arr) {
    if (arr.size() == 0) {
      return arr;
    }
    accumulate_all_general<InpType,f,InpType>(arr, arr);
    return arr;
  }

  template <typename f, typename InpType, typename IAx>
  inline InpType& accumulate_axis_inplace(InpType& arr, const IAx& ax) {
    if (arr.size() == 0) {
      return arr;
    }
    accumulate_axis_general<InpType,f,InpType,IAx>(arr, arr, ax);
    return arr;
  }
}

#endif
