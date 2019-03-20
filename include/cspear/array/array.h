#ifndef CSPEAR_ARRAY_ARRAY_H
#define CSPEAR_ARRAY_ARRAY_H

#include <cstring>
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <cspear/tools/assert.h>
#include <cspear/tools/misc.h>
#include <cspear/tools/types.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/iterators/ewise-iterator.h>

namespace csp {
  template <typename T, typename I=tools::Int,
            template<typename> typename View=ContiguousView>
  class array {
    T* data_;
    View<I> view_;

    I prev_allocated_size_ = 0;
    bool allocated_ = false; // flag to indicate if the data is allocated by us

    public:
    // define the datatype and expose it to public
    using DataType = T;
    using IndexType = I;
    using ViewType = View<I>;

    // constructors and destructor
    array();
    array(std::initializer_list<T> elmts);
    array(const T* a, I sz);
    array(const T* a, std::initializer_list<I> shape);
    array(const array<T,I,View>& a);
    template <template <typename> typename View2>
    array(const array<T,I,View2>& a);
    ~array();

    // internal constructor that does not own the data
    // (only for different memory view)
    array(T* a, View<I>&& view);

    // static initializers
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
    array<T,I,FilterView> operator[](const array<bool,I,ContiguousView>& filter);

    // assignment operator and copy
    array<T,I,ContiguousView>& operator=(const array<T,I,View>& a);
    array<T,I,ContiguousView> copy() const;

    // parameters
    T* data() { return data_; }
    const T* data() const { return data_; }
    const View<I>& view() const { return view_; }
    inline I size() const { return view_.size(); }
    I ndim() const { return shape().size(); }
    inline const std::vector<I>& shape() const { return view_.shape(); }

    // casting and device movement
    template <typename T2> array<T2,I,View> astype() const; // ???

    // reshape and resize
    array<T,I,View>& resize(I sz);
    array<T,I,View>& reshape(std::initializer_list<I> shape);
    array<T,I,View>& reshape(const std::vector<I>& shape);
    array<T,I,View>& squeeze();
    array<T,I,View>& expand_dims(I idx);
    array<T,I,View>& ravel();

    /*************** OPERATORS ***************/
    // unary operators (non inplace)
    array<T,I,ContiguousView> operator-();
    array<T,I,ContiguousView> operator+(T a);
    array<T,I,ContiguousView> operator-(T a);
    array<T,I,ContiguousView> operator*(T a);
    array<T,I,ContiguousView> operator/(T a);
    array<T,I,ContiguousView> reciprocal(T a); // returns a / this
    array<T,I,ContiguousView> clip_lb(T lb);
    array<T,I,ContiguousView> clip_ub(T ub);
    array<T,I,ContiguousView> clip(T lb, T ub);
    array<bool,I,ContiguousView> operator!();
    array<bool,I,ContiguousView> operator>(T a);
    array<bool,I,ContiguousView> operator>=(T a);
    array<bool,I,ContiguousView> operator<(T a);
    array<bool,I,ContiguousView> operator<=(T a);
    array<bool,I,ContiguousView> operator==(T a);
    array<bool,I,ContiguousView> operator&&(T a);
    array<bool,I,ContiguousView> operator||(T a);

    // inplace unary operators
    array<T,I,View>& operator+=(T a);
    array<T,I,View>& operator-=(T a);
    array<T,I,View>& operator*=(T a);
    array<T,I,View>& operator/=(T a);
    array<T,I,View>& reciprocal_(T a);
    array<T,I,View>& clip_lb_(T lb);
    array<T,I,View>& clip_ub_(T ub);
    array<T,I,View>& clip_(T lb, T ub);

    // binary operators (non inplace)
    template <template<typename> typename View2>
    array<T,I,ContiguousView> operator+(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,ContiguousView> operator-(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,ContiguousView> operator*(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,ContiguousView> operator/(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator>(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator>=(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator<(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator<=(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator==(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator&&(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<bool,I,ContiguousView> operator||(const array<T,I,View2>& a);

    // inplace binary operators
    template <template<typename> typename View2>
    array<T,I,View>& operator+=(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,View>& operator-=(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,View>& operator*=(const array<T,I,View2>& a);
    template <template<typename> typename View2>
    array<T,I,View>& operator/=(const array<T,I,View2>& a);

    private:
    void _realloc();
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
    static_assert(std::is_same<View<I>,ContiguousView<I> >::value);
    _copy_different_view(a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::~array() {
    if (allocated_) {
      std::free(data_);
    }
  }

  // internal constructor for memory view of the same data
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>::array(T* a, View<I>&& view) {
    data_ = a;
    view_ = view;
  }

  // static initializer
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::empty(const std::vector<I>& shape) {
    array<T,I,ContiguousView> res;
    I sz = tools::_prod_init_list(shape);
    res.resize(sz).reshape(shape);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::zeros(const std::vector<I>& shape) {
    array<T,I,ContiguousView> res = empty(shape);
    std::memset(res.data(), 0, res.size()*sizeof(T));
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::ones(const std::vector<I>& shape) {
    array<T,I,ContiguousView> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)1);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::full(const std::vector<I>& shape, T value) {
    array<T,I,ContiguousView> res = empty(shape);
    std::fill(res.data(), res.data()+res.size(), (T)value);
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::arange(T begin, T end, T range) {
    array<T,I,ContiguousView> res;
    I sz = (end - begin) / range;
    res.resize(sz);
    auto it = EWiseIterator<T,I,ContiguousView<I> >(res.data(), res.view());
    for (T i = begin; i < end; i+=range, ++it) {
      *it = i;
    }
    return res;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::arange(T end) {
    return arange((T)0, end, (T)1);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::arange(T begin, T end) {
    return arange(begin, end, (T)1);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::linspace(T begin, T end, I n) {
    array<T,I,ContiguousView> res;
    res.resize(n);
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
  inline array<T,I,FilterView> array<T,I,View>::operator[](
               const array<bool,I,ContiguousView>& filter) {
    return array<T,I,FilterView>(data_, FilterView<I>(filter));
  }

  // assignment operator and copy
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView>& array<T,I,View>::operator=(const array<T,I,View>& a) {
    if (this == &a) {
      return *this;
    }

    if (std::is_same<ContiguousView<I>,View<I> >::value) {
      _copy(a);
    }
    else {
      _copy_different_view(a);
    }
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::copy() const {
    array<T,I,ContiguousView> res(*this);
    return res;
  }

  // resize and reshaped
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::resize(I sz) {
    if (view_.size() == sz) {
      return *this;
    }
    else {
      view_.reshape({sz}); // make it a one-dimensional array
      _realloc();
      return *this;
    }
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reshape(std::initializer_list<I> shape) {
    I sz = tools::_prod_init_list(shape);
    _cspear_assert(sz == view_.size(), "The size must stay the same");
    view_.reshape(shape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reshape(const std::vector<I>& shape) {
    I sz = tools::_prod_init_list(shape);
    _cspear_assert(sz == view_.size(), "The size must stay the same");
    view_.reshape(shape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::squeeze() {
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
  array<T,I,View>& array<T,I,View>::expand_dims(I idx) {
    _cspear_assert((idx >= 0) && (idx <= ndim()),
                   "Expanded index must be between [0,ndim()]");
    std::vector<I> newshape = shape();
    newshape.insert(&newshape[idx], (I)1);
    view_.reshape(newshape);
    return *this;
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::ravel() {
    view_.reshape({view.size()});
    return *this;
  }

  // private functions
  template <typename T, typename I, template<typename> typename View>
  void array<T,I,View>::_realloc() {
    I sz = view_.size();
    if (sz == prev_allocated_size_) {
      return;
    }

    if (allocated_) std::free(data_);
    data_ = (T*) std::malloc(sz*sizeof(*data_));
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
//     // unary (arithmetic) operations
//     array<T,I,View> operator-();
//
//     // binary (arithmetic) operations
//     /**begin repeatop
//     opname = ["operator+", "operator-", "operator*", "operator/"];
//     */
//     /**begin repeattype
//     tpename = ["const array<T,I,View>&", "T"];
//     */
//     array<T,I,View> @opname@(@tpename@ a);
//     /**end repeattype**/
//     /**end repeatop**/
//     array<T,I,View> rdiv(T a);
//
//     // binary (arithmetic) operations (inplace)
//     /**begin repeatop
//     opname = ["operator+=", "operator-=", "operator*=", "operator/="];
//     */
//     /**begin repeattype
//     tpename = ["const array<T,I,View>&", "T"];
//     */
//     array<T,I,View>& @opname@(@tpename@ a);
//     /**end repeattype**/
//     /**end repeatop**/
//     array<T,I,View>& rdiv_(T a);
//
//     // comparison operations
//     /**begin repeatop
//     cmpopname = ["operator>", "operator<", "operator>=", "operator<=",
//                   "operator==", "operator!="];
//     */
//     /**begin repeattype
//     tpename = ["const array<T,I,View>&", "T"];
//     */
//     array<bool,I> @cmpopname@(@tpename@);
//     /**end repeattype**/
//     /**end repeatop**/
//
//     // logical operations (only for array<bool,I>)
//
//     // binary logical operations
//     /**begin repeatop
//     boolopname = ["operator&&", "operator||"];
//     */
//     /**begin repeattype
//     tpename = ["const array<T,I,View>&", "T"];
//     */
//     array<bool,I> @boolopname@(@tpename@);
//     /**end repeattype**/
//     /**end repeatop**/
//
//     // unary logical operations
//     /**begin repeatop
//     boolopname = ["operator!"];
//     */
//     array<bool,I> @boolopname@();
//     /**end repeatop**/
//
//     // reduction operator
//     /**begin repeat
//     reducefn = ["sum", "max", "min", "mean", "std"];
//     */
//     T @reducefn@();
//     array<T,I,View> @reducefn@(I axis);
//     array<T,I,View> @reducefn@(std::initializer_list<I> axes);
//     /**end repeat**/
//
//     // math functions
//     /**begin repeat
//     mathfn = ["sin", "cos", "tan", "asin", "acos", "atan", "atan2",
//               "sinh", "cosh", "tanh", "asinh", "acosh", "atanh",
//               "exp", "log", "log10", "exp2", "expm1", "log1p", "log2",
//               "sqrt", "cbrt", "sqr", "cube",
//               "erf", "erfc", "tgamma", "lgamma",
//               "ceil", "floor", "round", "fabs"];
//     */
//     array<T,I,View> @mathfn@() const;
//     array<T,I,View>& @mathfn@_(); // in-place
//     /**end repeat**/
//
//     // misc functions
//     array<T,I,View> clip_lb(T lb) const;
//     array<T,I,View> clip_ub(T ub) const;
//     array<T,I,View> clip(T lb, T ub) const;
//     array<T,I,View>& clip_lb_(T lb);
//     array<T,I,View>& clip_ub_(T ub);
//     array<T,I,View>& clip_(T lb, T ub);
//
//     private:
//     void _realloc();
//     void _copy(const array<T,I,View>& a);
//   };
//   // assignment operator and copy
//   template <typename T, typename I, template<typename> typename View>
//   array<T,I,View>& array<T,I,View>::operator=(const array<T,I,View>& a) {
//     _copy(a);
//     return *this;
//   }
//
//   template <typename T, typename I, template<typename> typename View>
//   array<T,I,View> array<T,I,View>::copy() const {
//     array<T,I,View> res(*this);
//     return res;
//   }
//
// }

#endif
