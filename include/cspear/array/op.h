#ifndef CSPEAR_ARRAY_OP_H
#define CSPEAR_ARRAY_OP_H

#include <stdexcept>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>

namespace csp {
  // forward declaration of array
  template <typename T, typename I,
            template<typename> typename View> class array;

  template <typename T, typename I,
            template<typename> typename InpView,
            typename TR, typename IR,
            template<typename> typename ResView,
            typename F>
  array<TR,IR,ResView> unary_op(F&& f, const array<T,I,InpView>& arr) {
    array<TR,IR,ResView> res = array<T,I,ResView>::empty(arr.shape());

    // performing the iteration
    auto it1 = EWiseIterator<T ,I ,InpView>((T*)arr.data(), arr.view());
    auto itr = EWiseIterator<TR,IR,ResView>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++itr) {
      *itr = f(*it1);
    }
    return res;
  }

  template <typename T, typename I, template<typename> typename View,
            typename F>
  array<T,I,View>& inplace_unary_op(F&& f, array<T,I,View>& arr) {
    auto it1 = EWiseIterator<T,I,View>((T*)arr.data(), arr.view());
    for (; it1; ++it1) {
      f(*it1);
    }
    return arr;
  }

  template <typename T, typename I,
            template<typename> typename InpView1,
            template<typename> typename InpView2,
            typename TR, typename IR,
            template<typename> typename ResView,
            typename F>
  inline array<TR,IR,ResView> ewise_binary_op(F&& f,
                                     const array<T,I,InpView1>& arr1,
                                     const array<T,I,InpView2>& arr2) {
    // shape and size checking should be done outside this

    array<TR,IR,ResView> res = array<T,I,ResView>::empty(arr1.shape());

    // performing the iteration
    auto it1 = EWiseIterator<T,I,InpView1>((T*)arr1.data(), arr1.view());
    auto it2 = EWiseIterator<T,I,InpView2>((T*)arr2.data(), arr2.view());
    auto itr = EWiseIterator<TR,IR,ResView>((TR*)res.data(), res.view());
    for (; it1; ++it1, ++it2, ++itr) {
      *itr = f(*it1, *it2);
    }
    return res;
  }

  template <typename T, typename I,
            template<typename> typename InpView1,
            template<typename> typename InpView2,
            typename F>
  inline array<T,I,InpView1>& ewise_inplace_binary_op(F&& f,
                                    array<T,I,InpView1>& arr1,
                                    const array<T,I,InpView2>& arr2) {
    // shape and size checking should be done outside this

    // performing the iteration
    auto it1 = EWiseIterator<T,I,InpView1>((T*)arr1.data(), arr1.view());
    auto it2 = EWiseIterator<T,I,InpView2>((T*)arr2.data(), arr2.view());
    for (; it1; ++it1, ++it2) {
      f(*it1, *it2);
    }
    return arr1;
  }

  template <typename T, typename I,
            template<typename> typename InpView1,
            template<typename> typename InpView2,
            typename TR, typename IR,
            template<typename> typename ResView,
            typename F>
  array<TR,IR,ResView> binary_op(F&& f,
                               const array<T,I,InpView1>& arr1,
                               const array<T,I,InpView2>& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) {
      // element wise
      return ewise_binary_op<T,I,InpView1,InpView2,TR,IR,ResView>(f, arr1, arr2);
    }
    else {
      throw std::runtime_error("Invalid shape of the operator.\n");
    }
  }

  template <typename T, typename I,
            template<typename> typename InpView1,
            template<typename> typename InpView2,
            typename F>
  array<T,I,InpView1>& inplace_binary_op(F&& f,
                               array<T,I,InpView1>& arr1,
                               const array<T,I,InpView2>& arr2) {
    // check the shape and decide if it is element-wise or broadcases
    if (arr1.shape() == arr2.shape()) {
      // element wise
      return ewise_inplace_binary_op<T,I,InpView1,InpView2>(f, arr1, arr2);
    }
    else {
      throw std::runtime_error("Invalid shape of the operator.\n");
    }
  }
}

#endif
