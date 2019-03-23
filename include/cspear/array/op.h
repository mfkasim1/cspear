#ifndef CSPEAR_ARRAY_OP_H
#define CSPEAR_ARRAY_OP_H

#include <stdexcept>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>
#include <cspear/iterators/bcast-iterator.h>

namespace csp {
  template <typename ResType, typename InpType, typename F>
  ResType unary_op(F&& f, const InpType& arr) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    ResType res = ResType::empty(arr.shape());

    // performing the iteration
    auto it1 = EWiseIterator<T,I,View>((T*)arr.data(), arr.view());
    auto itr = EWiseIterator<TR,IR,ViewR>((TR*)res.data(),
                               res.view());
    // auto itr = EWiseIterator<TR,IR,ResView>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++itr) {
      *itr = f(*it1);
    }
    return res;
  }

  template <typename InpType, typename F>
  InpType& inplace_unary_op(F&& f, InpType& arr) {
    using T = typename InpType::DataType;
    using I = typename InpType::IndexType;
    using View = typename InpType::ViewType;

    auto it1 = EWiseIterator<T,I,View>((T*)arr.data(), arr.view());
    for (; it1; ++it1) {
      f(*it1);
    }
    return arr;
  }

  template <typename ResType, typename InpType, typename T, typename F>
  inline ResType ewise_binary_op_with_val(F&& f,
                                          const InpType& arr,
                                          const T& val) {
    // shape and size checking should be done outside this

    ResType res = ResType::empty(arr.shape());

    using T1 = typename InpType::DataType;
    using I1 = typename InpType::IndexType;
    using View1 = typename InpType::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    auto it1 = EWiseIterator<T1,I1,View1>((T1*)arr.data(), arr.view());
    auto itr = EWiseIterator<TR,IR,ViewR>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++itr) {
      *itr = f(*it1, val);
    }
    return res;
  }

  template <typename InpType, typename T, typename F>
  inline InpType& ewise_inplace_binary_op_with_val(F&& f,
                                                   InpType& arr,
                                                   const T& val) {
    // shape and size checking should be done outside this

    using T1 = typename InpType::DataType;
    using I1 = typename InpType::IndexType;
    using View1 = typename InpType::ViewType;

    auto it = EWiseIterator<T1,I1,View1>((T1*)arr.data(), arr.view());
    for (; it; ++it) {
      f(*it, val);
    }
    return arr;
  }

  template <typename ResType, typename InpType1, typename InpType2, typename F>
  inline ResType ewise_binary_op(F&& f,
                                 const InpType1& arr1,
                                 const InpType2& arr2) {
    // shape and size checking should be done outside this

    ResType res = ResType::empty(arr1.shape());

    using T1 = typename InpType1::DataType;
    using I1 = typename InpType1::IndexType;
    using View1 = typename InpType1::ViewType;
    using T2 = typename InpType2::DataType;
    using I2 = typename InpType2::IndexType;
    using View2 = typename InpType2::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    // performing the iteration
    auto it1 = EWiseIterator<T1,I1,View1>((T1*)arr1.data(), arr1.view());
    auto it2 = EWiseIterator<T2,I2,View2>((T2*)arr2.data(), arr2.view());
    auto itr = EWiseIterator<TR,IR,ViewR>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++it2, ++itr) {
      *itr = f(*it1, *it2);
    }
    return res;
  }

  template <typename InpType1, typename InpType2, typename F>
  inline InpType1& ewise_inplace_binary_op(F&& f,
                                           InpType1& arr1,
                                           const InpType2& arr2) {
    // shape and size checking should be done outside this

    using T1 = typename InpType1::DataType;
    using I1 = typename InpType1::IndexType;
    using View1 = typename InpType1::ViewType;
    using T2 = typename InpType2::DataType;
    using I2 = typename InpType2::IndexType;
    using View2 = typename InpType2::ViewType;

    // performing the iteration
    auto it1 = EWiseIterator<T1,I1,View1>((T1*)arr1.data(), arr1.view());
    auto it2 = EWiseIterator<T2,I2,View2>((T2*)arr2.data(), arr2.view());
    for (; it1; ++it1, ++it2) {
      f(*it1, *it2);
    }
    return arr1;
  }

  template <typename ResType, typename InpType1, typename InpType2, typename F>
  void bcast_binary_op(ResType& res, F&& f, const InpType1& arr1,
                       const InpType2& arr2) {
    // extract the types
    using T1 = typename InpType1::DataType;
    using I1 = typename InpType1::IndexType;
    using View1 = typename InpType1::ViewType;
    using T2 = typename InpType2::DataType;
    using I2 = typename InpType2::IndexType;
    using View2 = typename InpType2::ViewType;
    using TR = typename ResType::DataType;
    using IR = typename ResType::IndexType;
    using ViewR = typename ResType::ViewType;

    // do the iterations
    auto itb = BCastIterator<T1,T2,TR,I1,View1,View2>(
        (T1*)arr1.data(), arr1.view(),
        (T2*)arr2.data(), arr2.view(),
        (TR*)res.data(), res.view());
    for (; itb; ++itb) {
      itb.result() = f(itb.first(), itb.second());
    }
  }

  template <typename ResType, typename InpType1, typename InpType2, typename F>
  ResType binary_op(F&& f, const InpType1& arr1, const InpType2& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) {
      // element wise
      return ewise_binary_op<ResType>(f, arr1, arr2);
    }
    else {
      // check if they are broadcastable
      auto resshape = bcast_output_shape(arr1.shape(), arr2.shape());
      if (resshape.size() == 0) {
        throw std::runtime_error("Invalid shape of the operator. "
          "They cannot be broadcasted.\n");
      }

      // do the broadcast
      ResType res = ResType::empty(resshape);
      bcast_binary_op(res, f, arr1, arr2);
      return res;
    }
  }

  template <typename InpType1, typename InpType2, typename F>
  InpType1& inplace_binary_op(F&& f,
                              InpType1& arr1,
                              const InpType2& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) {
      // element wise
      return ewise_inplace_binary_op(f, arr1, arr2);
    }
    else {
      throw std::runtime_error("Invalid shape of the operator.\n");
    }
  }
}

#endif
