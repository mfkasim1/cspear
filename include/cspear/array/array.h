#ifndef CSPEAR_ARRAY_ARRAY_H
#define CSPEAR_ARRAY_ARRAY_H

#include <cstring>
#include <cmath>
#include <vector>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <cspear/array/macro-op.h>
#include <cspear/array/macro-reduce.h>
#include <cspear/array/macro-accumulate.h>
#include <cspear/array/ufuncs.h>
#include <cspear/array/ufuncs-math.h>
#include <cspear/lib/idx.h>
#include <cspear/tools/assert.h>
#include <cspear/tools/misc.h>
#include <cspear/tools/types.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/views/slice-view.h>
#include <cspear/iterators/ewise-iterator.h>

namespace csp {
  template <typename T, typename I=tools::Int,
            template<typename> typename View=ContiguousView>
  class array {
    T* data_ = NULL;
    View<I> view_ = View<I>();

    I prev_allocated_size_ = 0;
    bool allocated_ = false; // flag to indicate if the data is allocated by us
    bool own_ = true; // flag to indicate if the array owns the memory
                      // (if the array is a view, own_ == false)
    std::shared_ptr<T> dataptr_ = NULL; // the pointer to the beginning of the data in memory
                 // this is to check if the operands and the assignee share
                 // the same memory to avoid aliasing

    public:
    // define the datatype and expose it to public
    using DataType = T;
    using IndexType = I;
    using ViewType = View<I>;

    // constructors and destructor
    array();
    array(std::initializer_list<T> elmts);
    array(std::initializer_list< std::initializer_list<T> > elmts);
    array(const T* a, I sz);
    array(const T* a, std::initializer_list<I> shape);
    array(const array<T,I,View>& a);
    template <template <typename> typename View2>
    array(const array<T,I,View2>& a);
    ~array();

    // internal constructor that does not own the data
    // (only for different memory view)
    array(T* a, View<I>&& view, const std::shared_ptr<T>& aptr);

    // static initializers
    static array<T,I,ContiguousView> wrap(T* a, I sz);
    static array<T,I,ContiguousView> empty(const std::vector<I>& shape);
    static array<T,I,ContiguousView> zeros(const std::vector<I>& shape);
    static array<T,I,ContiguousView> ones(const std::vector<I>& shape);
    static array<T,I,ContiguousView> full(const std::vector<I>& shape, T value);
    static array<T,I,ContiguousView> arange(T begin, T end, T range);
    static array<T,I,ContiguousView> arange(T end);
    static array<T,I,ContiguousView> arange(T begin, T end);
    static array<T,I,ContiguousView> linspace(T begin, T end, I n);

    // indexing
    T& operator[](I idx);
    const T& operator[](I idx) const;
    // filter views
    array<T,I,FilterView> filter(const array<bool,I,ContiguousView>& f) const;
    // at (returns contiguous views)
    array<T,I,ContiguousView> at(I idx) const; // get the first dimension
    array<T,I,ContiguousView> at(I idx0, I idx1) const; // get the first dimension slice
    T& at(std::initializer_list<I> idxs);
    T& at(const std::vector<I>& idxs);
    const T& at(std::initializer_list<I> idxs) const;
    const T& at(const std::vector<I>& idxs) const;
    // slice views
    template <template<typename> typename Vec=std::initializer_list>
    array<T,I,SliceView> slice(const Vec< Slice<I> >& s) const;

    // assignment operator and copy
    array<T,I,ContiguousView>& operator=(const array<T,I,View>& a);
    template <template<typename> typename View2>
    array<T,I,View>& operator=(const array<T,I,View2>& a);
    array<T,I,ContiguousView> copy() const;

    // parameters
    inline T* data() { return data_; }
    inline std::shared_ptr<T>& dataptr() { return dataptr_; }
    inline const std::shared_ptr<T>& dataptr() const { return dataptr_; }
    inline const T* data() const { return data_; }
    inline T* begin() { return data_; }
    inline T* end() { return data_ + size(); }
    inline const T* begin() const { return data_; }
    inline const T* end() const { return data_ + size(); }
    inline const View<I>& view() const { return view_; }
    inline I size() const { return view_.size(); }
    inline I ndim() const { return shape().size(); }
    inline const std::vector<I>& shape() const { return view_.shape(); }

    // casting and device movement
    template <typename T2> array<T2,I,View> astype() const; // ???

    // reshape and resize
    array<T,I,View>& resize_(I sz);
    array<T,I,View>& reshape_(std::initializer_list<I> shape);
    array<T,I,View>& reshape_(const std::vector<I>& shape);
    array<T,I,View>& squeeze_();
    array<T,I,View>& expand_dims_(I idx);
    array<T,I,View>& ravel_();

    /**************** REDUCE ****************/
    CSPEAR_REDUCE(sum,ufunc::add,false);
    CSPEAR_REDUCE(prod,ufunc::mult,false);
    CSPEAR_REDUCE(max,ufunc::max,true);
    CSPEAR_REDUCE(min,ufunc::min,true);
    CSPEAR_REDUCE(all,ufunc::logical_and,false);
    CSPEAR_REDUCE(any,ufunc::logical_or,false);

    /**************** ACCUMULATE ****************/
    CSPEAR_ACCUMULATE(cumsum,ufunc::add);
    CSPEAR_ACCUMULATE(cumprod,ufunc::mult);
    CSPEAR_ACCUMULATE(cummax,ufunc::max);
    CSPEAR_ACCUMULATE(cummin,ufunc::min);

    /*************** OPERATORS ***************/
    // arithmetic operators
    CSPEAR_UNARY_OP_NOT_INPLACE(operator-,ufunc::neg);
    CSPEAR_BINARY_OP_NOT_INPLACE(operator+,ufunc::add);
    CSPEAR_BINARY_OP_NOT_INPLACE(operator-,ufunc::sub);
    CSPEAR_BINARY_OP_NOT_INPLACE(operator*,ufunc::mult);
    CSPEAR_BINARY_OP_NOT_INPLACE(operator/,ufunc::div);
    CSPEAR_BINARY_OP(reciprocal,ufunc::reciprocal);
    CSPEAR_BINARY_OP_INPLACE(operator+=,ufunc::add);
    CSPEAR_BINARY_OP_INPLACE(operator-=,ufunc::sub);
    CSPEAR_BINARY_OP_INPLACE(operator*=,ufunc::mult);
    CSPEAR_BINARY_OP_INPLACE(operator/=,ufunc::div);
    CSPEAR_UNARY_OP(neg,ufunc::neg);
    CSPEAR_BINARY_OP(add,ufunc::add);
    CSPEAR_BINARY_OP(sub,ufunc::sub);
    CSPEAR_BINARY_OP(mult,ufunc::mult);
    CSPEAR_BINARY_OP(div,ufunc::div);

    // comparison operators
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator>,ufunc::gt);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator>=,ufunc::gteq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator<,ufunc::lt);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator<=,ufunc::lteq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator==,ufunc::eq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator!=,ufunc::neq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(gt,ufunc::gt);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(gteq,ufunc::gteq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(lt,ufunc::lt);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(lteq,ufunc::lteq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(eq,ufunc::eq);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(neq,ufunc::neq);

    // logical operators
    CSPEAR_UNARY_OP_NOT_INPLACE_TO_BOOL(operator!,ufunc::logical_not);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator&&,ufunc::logical_and);
    CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(operator||,ufunc::logical_or);

    // clip operations
    CSPEAR_TERNARY_OP(clip,ufunc::clip);
    CSPEAR_BINARY_OP(maximum,ufunc::max);
    CSPEAR_BINARY_OP(minimum,ufunc::min);

    // fill / assignment operators
    CSPEAR_BINARY_OP(fill,ufunc::assign);

    // math operations
    CSPEAR_UNARY_OP(cos,ufunc::cos);
    CSPEAR_UNARY_OP(sin,ufunc::sin);
    CSPEAR_UNARY_OP(tan,ufunc::tan);
    CSPEAR_UNARY_OP(acos,ufunc::acos);
    CSPEAR_UNARY_OP(asin,ufunc::asin);
    CSPEAR_UNARY_OP(atan,ufunc::atan);
    CSPEAR_BINARY_OP(atan2,ufunc::atan2);
    CSPEAR_UNARY_OP(cosh,ufunc::cosh);
    CSPEAR_UNARY_OP(sinh,ufunc::sinh);
    CSPEAR_UNARY_OP(tanh,ufunc::tanh);
    CSPEAR_UNARY_OP(acosh,ufunc::acosh);
    CSPEAR_UNARY_OP(asinh,ufunc::asinh);
    CSPEAR_UNARY_OP(atanh,ufunc::atanh);
    CSPEAR_UNARY_OP(exp,ufunc::exp);
    CSPEAR_UNARY_OP(log,ufunc::log);
    CSPEAR_UNARY_OP(log10,ufunc::log10);
    CSPEAR_UNARY_OP(exp2,ufunc::exp2);
    CSPEAR_UNARY_OP(expm1,ufunc::expm1);
    CSPEAR_UNARY_OP(log1p,ufunc::log1p);
    CSPEAR_UNARY_OP(log2,ufunc::log2);
    CSPEAR_BINARY_OP(pow,ufunc::pow);
    CSPEAR_UNARY_OP(sqrt,ufunc::sqrt);
    CSPEAR_UNARY_OP(cbrt,ufunc::cbrt);
    CSPEAR_BINARY_OP(hypot,ufunc::hypot);
    CSPEAR_UNARY_OP(erf,ufunc::erf);
    CSPEAR_UNARY_OP(erfc,ufunc::erfc);
    CSPEAR_UNARY_OP(tgamma,ufunc::tgamma);
    CSPEAR_UNARY_OP(lgamma,ufunc::lgamma);
    CSPEAR_UNARY_OP(ceil,ufunc::ceil);
    CSPEAR_UNARY_OP(trunc,ufunc::trunc);
    CSPEAR_UNARY_OP(floor,ufunc::floor);
    CSPEAR_UNARY_OP(round,ufunc::round);
    CSPEAR_UNARY_OP(abs,ufunc::abs);

    private:
    template <int n = 1> void _realloc();
    void _calloc();
    void _copy(const array<T,I,View>& a);
    template <template<typename> typename View2>
    void _copy_different_view(const array<T,I,View2>& a);
  };

  // implementations

  // constructors and destructor
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array() {}

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(std::initializer_list<T> elmts) {
    // set the view
    I sz = elmts.size();
    view_.reshape({sz});

    // copy the data
    _realloc();
    std::copy(elmts.begin(), elmts.end(), data_);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(std::initializer_list< std::initializer_list<T> > elmts) {
    // get the shape
    I ndim0 = elmts.size();
    I ndim1 = elmts.begin()->size();
    for (auto it = elmts.begin() + 1; it != elmts.end(); ++it) {
      if (it->size() != ndim1) {
        throw std::runtime_error("The size must match.");
      }
    }
    std::vector<I> shape = {ndim0, ndim1};
    view_.reshape(shape);

    // reallocate and copy the data
    _realloc();
    I k = 0;
    for (auto it0 = elmts.begin(); it0 != elmts.end(); ++it0) {
      for (auto it1 = it0->begin(); it1 != it0->end(); ++it1) {
        data_[k++] = *it1;
      }
    }
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(const T* a, I sz) {
    // set the view
    view_.reshape({sz});

    // copy the data
    _realloc();
    std::copy(a, a+sz, data_);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(const T* a, std::initializer_list<I> shape) {
    // get the size
    view_.reshape(shape);

    // copy the data
    _realloc();
    std::copy(a, a+view_.size(), data_);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(const array<T,I,View>& a) {
    // copy the array to self
    _copy(a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>::array(const array<T,I,View2>& a) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
        "Copy operation can only be done to an array with ContiguousView.");
    _copy_different_view(a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::~array() {
    if (allocated_) {
      dataptr_.reset();
      data_ = NULL;
      allocated_ = false;
    }
  }

  // internal constructor for memory view of the same data
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(T* a, View<I>&& view, const std::shared_ptr<T>& aptr) {
    data_ = a;
    view_ = view;
    own_ = false;
    dataptr_ = aptr;
  }

  // static initializer
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::wrap(T* a, I sz) {
    return array(a, ContiguousView<I>({sz}), a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::empty(const std::vector<I>& shape) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res;
    I sz = tools::_prod_init_list(shape);
    res.resize_(sz).reshape_(shape);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::zeros(const std::vector<I>& shape) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res;
    res.view_.reshape(shape);
    res.template _realloc<0>();
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::ones(const std::vector<I>& shape) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)1);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::full(const std::vector<I>& shape, T value) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)value);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::arange(T begin, T end, T range) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res;
    I sz = (I)std::ceil((end - begin) / range);
    sz = (sz < 0) ? 0 : sz;
    res.resize_(sz);
    auto it = EWiseIterator<T,I,ContiguousView<I> >(res.data(), res.view());
    for (T i = begin; it; i+=range, ++it) {
      *it = i;
    }
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  inline array<T,I,ContiguousView> array<T,I,View>::arange(T end) {
    return arange((T)0, end, (T)1);
  }

  template <typename T, typename I, template<typename> typename View>
  inline array<T,I,ContiguousView> array<T,I,View>::arange(T begin, T end) {
    return arange(begin, end, (T)1);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::linspace(T begin, T end, I n) {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Static initializer only works for contiguous view array");

    array<T,I,ContiguousView> res;
    res.resize_(n);
    T di = n > 1 ? (end - begin) / (n - 1) : 1;
    auto it = EWiseIterator<T,I,ContiguousView<I> >(res.data(), res.view());
    T i = begin;
    for (; it; ++it) {
      *it = i;
      i += di;
    }
    return res;
  }

  // indexing
  template <typename T, typename I, template<typename> typename View>
  inline T& array<T,I,View>::operator[](I idx) {
    return data_[view_.idx(idx)];
  }

  template <typename T, typename I, template<typename> typename View>
  inline const T& array<T,I,View>::operator[](I idx) const {
    return data_[view_.idx(idx)];
  }

  template <typename T, typename I, template<typename> typename View>
  inline array<T,I,FilterView> array<T,I,View>::filter(
               const array<bool,I,ContiguousView>& fltr) const {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Only array with contiguous view can do filtering. Please do .copy() to "
      "get the contiguous copy of this array.");
    _cspear_assert(fltr.shape() == shape(),
      "Filter's shape mismatches");
    return array<T,I,FilterView>(data_,
                  FilterView<I>(fltr.data(), fltr.size()), dataptr_);
  }

  template <typename T, typename I, template<typename> typename View>
  inline array<T,I,ContiguousView> array<T,I,View>::at(I idx) const {
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Only array with contiguous view can do indexing. Please do .copy() to "
      "get the contiguous copy of this array.");
    auto& sh = shape();
    _cspear_assert((idx >= 0) && (idx < sh[0]),
      "Index is out of the range");

    // get the newshape
    std::vector<I> newshape;
    if (ndim() == 1) {
      newshape.push_back(1);
    }
    else {
      newshape.resize(ndim()-1);
      std::copy(sh.begin()+1, sh.end(), newshape.begin());
    }
    I stride = size() / sh[0];
    return array<T,I,ContiguousView>(data_ + idx * stride,
                     ContiguousView<I>(newshape), dataptr_);
  }

  template <typename T, typename I, template<typename> typename View>
  inline array<T,I,ContiguousView> array<T,I,View>::at(I idx0, I idx1) const {
    // check the type
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Only array with contiguous view can do indexing. Please do .copy() to "
      "get the contiguous copy of this array.");

    // check the input index
    auto& sh = shape();
    _cspear_assert(idx1 >= idx0,
      "The end index must be larger or equal to the beginning index");

    if ((idx0 >= sh[0]) || (idx1 == idx0) || (sh[0] == 0)) {
      std::vector<I> newshape({0});
      return array<T,I,ContiguousView>(data_,
        ContiguousView<I>(newshape), dataptr_);
    }

    _cspear_assert((idx0 >= 0) && (idx1 >= 0),
      "Index cannot be negative");

    // get the newshape
    if (idx1 > sh[0]) idx1 = sh[0];

    std::vector<I> newshape = sh;
    newshape[0] = idx1 - idx0;

    I stride = size() / sh[0];
    return array<T,I,ContiguousView>(data_ + idx0 * stride,
                     ContiguousView<I>(newshape), dataptr_);
  }

  template <typename T, typename I, template<typename> typename View>
  inline T& array<T,I,View>::at(std::initializer_list<I> idxs) {
    return const_cast<T&>(const_cast<const array<T,I,View>*>(this)->at(idxs));
  }

  template <typename T, typename I, template<typename> typename View>
  inline T& array<T,I,View>::at(const std::vector<I>& idxs) {
    return const_cast<T&>(const_cast<const array<T,I,View>*>(this)->at(idxs));
  }

  template <typename T, typename I, template<typename> typename View>
  inline const T& array<T,I,View>::at(std::initializer_list<I> idxs) const {
    std::vector<I> i = idxs;
    return at(i);
  }

  template <typename T, typename I, template<typename> typename View>
  inline const T& array<T,I,View>::at(const std::vector<I>& idxs) const {
    _cspear_assert(idxs.size() == ndim(),
                  "The indices length must match the dimension");
    // ravel indices
    I idx = ravel_index(idxs, shape());
    return operator[](idx);
  }

  // slice views
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename Vec>
  array<T,I,SliceView> array<T,I,View>::slice(const Vec< Slice<I> >& s) const {
    // do checking here
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value,
      "Only array with contiguous view can do slicing. Please do .copy() to "
      "get the contiguous copy of this array.");
    _cspear_assert(s.size() == ndim(), "Invalid length of the slices.");

    // get the unravel index of the slice's beginning
    I idx = 0;
    auto& sh = shape();
    I stride = size();
    I i = 0;
    for (auto& slice : s) {
      stride /= sh[i];
      idx += slice.begin * stride;
      ++i;
    }

    return array<T,I,SliceView>(data_+idx, SliceView<I>(s, sh), dataptr_);
  }

  // assignment operator and copy
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView>& array<T,I,View>::operator=(const array<T,I,View>& a) {
    if (this == &a) {
      return *this;
    }

    if (own_) {
      if (std::is_same<ContiguousView<I>,View<I> >::value) {
        _copy(a);
      }
      else {
        _copy_different_view(a);
      }
    }
    else {
      // if the array does not own the memory, invoke fill_ operation
      fill_(a);
    }
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  inline array<T,I,View>& array<T,I,View>::operator=(const array<T,I,View2>& a) {
    return fill_(a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::copy() const {
    array<T,I,ContiguousView> res(*this);
    return res;
  }

  // resize and reshaped
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::resize_(I sz) {
    if (view_.size() == sz) {
      return *this;
    }
    else if (!own_) {
      throw std::runtime_error("Array that does not own memory cannot be "
          "resized. Please make a copy of this array first with .copy()");
    }
    else if (dataptr_.use_count() > 1) {
      throw std::runtime_error("This array has stored view(s). Resizing this "
          "would invalidate the view(s).");
    }
    else {
      view_.reshape({sz}); // make it a one-dimensional array
      _realloc();
      return *this;
    }
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reshape_(std::initializer_list<I> shape) {
    I sz = tools::_prod_init_list(shape);
    _cspear_assert(sz == view_.size(), "The size must stay the same");
    view_.reshape(shape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reshape_(const std::vector<I>& shape) {
    I sz = tools::_prod_init_list(shape);
    _cspear_assert(sz == view_.size(), "The size must stay the same");
    view_.reshape(shape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::squeeze_() {
    I nd = ndim();
    if (nd <= 1) {
      return *this;
    }

    // get the new shape
    std::vector<I> newshape;
    newshape.reserve(nd);
    const std::vector<I>& shape = view_.shape();
    for (I i = 0; i < nd; ++i) {
      if (shape[i] == 1) continue;
      newshape.push_back(shape[i]);
    }
    view_.reshape(newshape);

    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::expand_dims_(I idx) {
    _cspear_assert((idx >= 0) && (idx <= ndim()),
                   "Expanded index must be between [0,ndim()]");
    std::vector<I> newshape = shape();
    newshape.insert(newshape.begin()+idx, (I)1);
    view_.reshape(newshape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::ravel_() {
    view_.reshape({view_.size()});
    return *this;
  }

  // private functions
  template <typename T, typename I, template<typename> typename View>
  template <int n>
  void array<T,I,View>::_realloc() {
    I sz = view_.size();
    if (sz == prev_allocated_size_) {
      return;
    }

    if (n != 0) {
      data_ = (T*) std::malloc(sz*sizeof(*data_));
    }
    else {
      data_ = (T*) std::calloc(sz, sizeof(*data_));
    }
    dataptr_.reset(data_, std::free);
    tools::_assert_cpu(data_, "CPU memory allocation failed.");
    allocated_ = true;
    prev_allocated_size_ = sz;
  }

  template <typename T, typename I, template<typename> typename View>
  void array<T,I,View>::_copy(const array<T,I,View>& a) {
    // copy the shape
    view_.reshape(a.shape());
    I sz = view_.size();

    // copy the data
    _realloc();
    std::copy(a.data(), a.data()+sz, data_);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  void array<T,I,View>::_copy_different_view(const array<T,I,View2>& a) {
    // set the view
    view_.reshape(a.shape());

    // copy the data
    _realloc();
    auto itr = EWiseIterator<T,I,View<I> >(data_, view_);
    auto ita = EWiseIterator<T,I,View2<I> >((T*)a.data(), a.view());
    for (; ita; ++ita, ++itr) {
      *itr = *ita;
    }
  }
}

#endif
