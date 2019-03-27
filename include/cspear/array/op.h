#ifndef CSPEAR_ARRAY_OP_H
#define CSPEAR_ARRAY_OP_H

#include <stdexcept>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>
#include <cspear/iterators/bcast-iterator.h>

namespace csp {
  template <typename ResType, typename f, typename InpType>
  ResType unary_op(const InpType& arr) {
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
      *itr = f::unary(*it1);
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

  template <typename ResType, typename f, typename InpType, typename T>
  inline ResType ewise_binary_op_with_val(const InpType& arr,
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
      *itr = f::binary(*it1, val);
    }
    return res;
  }

  template <typename f, typename InpType, typename T>
  inline InpType& ewise_inplace_binary_op_with_val(InpType& arr,
                                                   const T& val) {
    // shape and size checking should be done outside this

    using T1 = typename InpType::DataType;
    using I1 = typename InpType::IndexType;
    using View1 = typename InpType::ViewType;

    auto it = EWiseIterator<T1,I1,View1>((T1*)arr.data(), arr.view());
    for (; it; ++it) {
      *it = f::binary(*it, val);
    }
    return arr;
  }

  template <typename ResType, typename f, typename InpType1, typename InpType2>
  inline ResType ewise_binary_op(const InpType1& arr1,
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
      *itr = f::binary(*it1, *it2);
    }
    return res;
  }

  template <typename f, typename InpType1, typename InpType2>
  inline InpType1& ewise_inplace_binary_op(InpType1& arr1,
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
      *it1 = f::binary(*it1, *it2);
    }
    return arr1;
  }

  template <typename f, typename ResType, typename InpType1, typename InpType2>
  void bcast_binary_op(ResType& res, const InpType1& arr1,
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
      itb.result() = f::binary(itb.first(), itb.second());
    }
  }

  template <typename f, typename InpType1, typename InpType2>
  inline InpType1& bcast_inplace_binary_op(InpType1& arr1,
                               const InpType2& arr2) {
    // bcast_binary_op(arr1, f, arr1, arr2);
    // return arr1;

    // extract the types
    using T1 = typename InpType1::DataType;
    using I1 = typename InpType1::IndexType;
    using View1 = typename InpType1::ViewType;
    using T2 = typename InpType2::DataType;
    using I2 = typename InpType2::IndexType;
    using View2 = typename InpType2::ViewType;

    // do the iterations
    auto itb = BCastIterator<T1,T2,T1,I1,View1,View2>(
    (T1*)arr1.data(), arr1.view(),
    (T2*)arr2.data(), arr2.view(),
    (T1*)arr1.data(), arr1.view());
    for (; itb; ++itb) {
      itb.result() = f::binary(itb.first(), itb.second());
    }
    return arr1;
  }

  template <typename ResType, typename f, typename InpType1, typename InpType2>
  ResType binary_op(const InpType1& arr1, const InpType2& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) {
      // element wise
      return ewise_binary_op<ResType, f>(arr1, arr2);
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
      bcast_binary_op<f>(res, arr1, arr2);
      return res;
    }
  }

  template <typename f, typename InpType1, typename InpType2>
  InpType1& inplace_binary_op(InpType1& arr1,
                              const InpType2& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) { // element wise
      // check aliasing
      if (arr1.dataptr() == arr2.dataptr()) { // possible aliasing
        auto res = arr1.copy();
        arr1 = ewise_inplace_binary_op<f>(res, arr2);
        return arr1;
      }
      else {
        return ewise_inplace_binary_op<f>(arr1, arr2);
      }
    }
    else {
      // check if they are broadcastable
      auto resshape = bcast_output_shape(arr1.shape(), arr2.shape());
      if (resshape.size() == 0) {
        throw std::runtime_error("Invalid shape of the operator.");
      }
      else if (resshape == arr1.shape()) {
        // check aliasing
        if (arr1.dataptr() == arr2.dataptr()) { // possible aliasing could happen
          auto res = arr1.copy();
          arr1 = bcast_inplace_binary_op<f>(res, arr2);;
          return arr1;
        }
        else {
          return bcast_inplace_binary_op<f>(arr1, arr2);
        }
      }
      else {
        throw std::runtime_error("Inplace broadcasting with different result "
                                 "shape is disabled to avoid aliasing.");
      }
    }
  }
}

#endif
