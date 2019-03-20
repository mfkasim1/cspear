#ifndef CSPEAR_ITERATORS_BCAST_ITERATOR_H
#define CSPEAR_ITERATORS_BCAST_ITERATOR_H

#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>

namespace csp {
  // broadcast iterator
  // The result view must always be ContiguousView

  template <typename T, typename I, typename View1, typename View2>
  class BCastIterator {
    public:
    // constructor
    BCastIterator(T* data1, const View1& view1,
                  T* data2, const View2& view2,
                  T* resdata, const ContiguousView<I>& viewr);

    // iterator operator
    T& first(); // reference to the element of the first data
    T& second(); // reference to the element of the second data
    T& result(); // reference to the element of the result data
    BCastIterator& operator++();
    operator bool() const;
  };

  // obtain the broadcast output shape
  // (out.size() == 0) if it can't be broadcasted
  std::vector<I> bcast_output_shape(const std::vector<I>& shape1,
                                    const std::vector<I>& shape2) {
    I ndim1 = shape1.size();
    I ndim2 = shape2.size();
    // make ndim(shape1) >= ndim(shape2)
    if (ndim1 < ndim2) {
      return bcast_output_shape(shape2, shape1);
    }

    std::vector<I> res(ndim1);
    auto it2 = shape2.rbegin();
    auto itr = res.rbegin();
    I elmt2;
    // iterate from the back
    for (auto it1 = shape1.rbegin(); it1 != shape1.rend(); ++it1, ++itr) {
      // get the shorter shape's element (and set to 1 if there's no more)
      elmt2 = (I)1;
      if (it2 != shape2.rend()) { elmt2 = *it2; }
      I& elmt1 = *it1;

      // decide the number of rows/cols in the given dimension
      I elmtr;
      if ((elmt2 == elmt1) || (elmt2 == 1)) {
        elmtr = elmt1;
      }
      else if (elmt1 == 1) {
        elmtr = elmt2;
      }
      else {
        // cannot be broadcasted, return zero element vector
        std::vector<I> zero();
        return zero;
      }
    }
    return res;
  }

  // partial template specialization for different views
  template <typename T, typename I>
  class BCastIterator<T,I,ContiguousView<I>,ContiguousView<I> > {
    // iterators
    T* it1_;
    T* it2_;
    T* itr_;
    I offset_;
    I sz_;

    public:
    // constructor
    BCastIterator(T* data1, const ContiguousView<I>& view1,
                  T* data2, const ContiguousView<I>& view2,
                  T* resdata, const ContiguousView<I>& viewr) {
      // ???

      // set the default parameters
      it1_ = data1;
      it2_ = data2;
      itr_ = datar;
      offset_ = 0;
      sz_ = viewr.size();
    }

    inline T& first() { return *it1_; }
    inline T& second() { return *it2_; }
    inline T& result() { return *itr_; }
    inline BCastIterator& operator++() {
      // it1 and it2 ???
      ++itr_;
      ++offset_;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
