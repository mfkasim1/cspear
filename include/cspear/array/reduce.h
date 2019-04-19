#ifndef CSPEAR_ARRAY_REDUCE_H
#define CSPEAR_ARRAY_REDUCE_H

#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>
#include <cspear/iterators/reduce-iterator.h>

namespace csp {
  template <typename f, bool error_if_empty=true, typename InpType>
  auto reduce_all(const InpType& arr) -> typename std::remove_const<decltype(f::identity)>::type {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename std::remove_const<decltype(f::identity)>::type;

    if (error_if_empty) {
      if (arr.size() == 0) {
        throw std::runtime_error("Reduce cannot be done with empty array.");
      }
    }

    TR res = f::identity;

    // performing the iteration
    for (auto it1 = arr.iterator(); it1; ++it1) {
      res = f::binary(res, *it1);
    }
    return res;
  }

  template <typename ResType, typename f, bool error_if_empty=true,
            typename InpType, typename IAx>
  ResType reduce_axis(const InpType& arr, const IAx& ax) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename std::remove_const<decltype(f::identity)>::type;

    if (arr.size() == 0) {
      if (error_if_empty) {
        throw std::runtime_error("Reduce cannot be done with empty array.");
      }
      else {
        return {};
      }
    }

    // check the axis
    _cspear_assert(((ax < arr.ndim()) && (ax >= 0)), "Out-of-the bound index");

    // get the shape of the result
    std::vector<IAx> axis = {ax};
    auto rshape = reduce_output_shape(axis, arr.shape());
    ResType res = ResType::full(rshape, f::identity);

    // performing the iteration
    auto it1 = ReduceIterator<T,I,View>(axis,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it1; ++it1) {
      auto& it1r = it1.result();
      it1r = f::binary(it1r, it1.first());
    }
    return res;
  }

  template <typename ResType, typename f, bool error_if_empty=true,
            typename InpType, typename AxType>
  ResType reduce_axes(const InpType& arr, const AxType& axes) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename std::remove_const<decltype(f::identity)>::type;

    if (arr.size() == 0) {
      if (error_if_empty) {
        throw std::runtime_error("Reduce cannot be done with empty array.");
      }
      else {
        return {};
      }
    }

    // order ax
    AxType ax = axes;
    std::sort(ax.begin(), ax.end());

    // get the shape of the result
    auto rshape = reduce_output_shape(ax, arr.shape());
    ResType res = ResType::full(rshape, f::identity);

    // performing the iteration
    auto it1 = ReduceIterator<T,I,View>(ax,
                      (T*)arr.data(), arr.view(),
                      (TR*)res.data(), res.view());
    for (; it1; ++it1) {
      auto& it1r = it1.result();
      it1r = f::binary(it1r, it1.first());
    }
    return res;
  }

  // arg reduce
  template <typename f, typename InpType>
  auto arg_reduce_all(const InpType& arr) -> typename std::remove_const<decltype(f::arg_identity)>::type {

    using IR = typename std::remove_const<decltype(f::arg_identity)>::type;
    using TR = typename std::remove_const<decltype(f::identity)>::type;

    // the array must not be empty
    _cspear_assert(arr.size() > 0, "Arg reduce cannot be done with empty array.");

    IR ir = f::arg_identity;
    TR r = f::identity;

    // do the iteration
    IR ib = 0;
    for (auto it1 = arr.iterator(); it1; ++it1, ++ib) {
      f::binary(r, *it1, ir, ib);
    }
    return ir;
  }
  template <typename ResType, typename f, typename InpType, typename IAx>
  ResType arg_reduce_axis(const InpType& arr, const IAx& ax) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename std::remove_const<decltype(f::identity)>::type;
    using IR = typename std::remove_const<decltype(f::arg_identity)>::type;
    typedef decltype(arr.copy()) ResDataType;

    // the array must not be empty
    _cspear_assert(arr.size() > 0, "Arg reduce cannot be done with empty array.");

    // check the axis
    _cspear_assert(((ax < arr.ndim()) && (ax >= 0)), "Out-of-the bound index");

    // get the shape of the result and initialize the result array
    std::vector<IAx> axis = {ax};
    auto rshape = reduce_output_shape(axis, arr.shape());
    ResDataType resdata = ResDataType::full(rshape, f::identity);
    ResType res = ResType::full(rshape, f::arg_identity);

    // performing the iteration (TODO: make it correct)
    auto it1 = ReduceIterator<T,I,View,true>(axis,
                      (T*)arr.data(), arr.view(),
                      (TR*)resdata.data(), resdata.view());
    for (; it1; ++it1) {
      auto& it1r = it1.result();
      auto ridx = it1.result_index();
      f::binary(it1r, it1.first(), res[ridx], it1.first_index());
    }
    return res;
  }

}

#endif
