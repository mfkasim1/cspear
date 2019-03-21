#ifndef CSPEAR_ITERATORS_BCAST_ITERATOR_H
#define CSPEAR_ITERATORS_BCAST_ITERATOR_H

#include <vector>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/iterators/stepback-iterator.h>

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
  template <typename I>
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
      if (it2 != shape2.rend()) {
        elmt2 = *it2;
        ++it2;
      }
      I elmt1 = *it1;

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
        std::vector<I> zero;
        return zero;
      }
      *itr = elmtr;
    }
    return res;
  }

  template <typename I>
  void _get_nsteps_nrepeats(
      const std::vector<I>& shape1,
      const std::vector<I>& shape2,
      std::vector<I>& nsteps1,
      std::vector<I>& nsteps2,
      std::vector<I>& nrepeats1,
      std::vector<I>& nrepeats2) {
    // it should be shape1.size() >= shape2.size()
    I ndim1 = shape1.size();
    I ndim2 = shape2.size();
    if (ndim2 > ndim1) {
      _get_nsteps_nrepeats(shape2, shape1,
          nsteps2, nsteps1, nrepeats2, nrepeats1);
      return;
    }
    // now ndim1 >= ndim2
    // reserve some memory
    nsteps1.reserve(ndim1);
    nsteps2.reserve(ndim1);
    nrepeats1.reserve(ndim1);
    nrepeats2.reserve(ndim1);

    // iterate from the end
    auto it2 = shape2.rbegin();
    for (auto it1 = shape1.rbegin(); it1 != shape1.rend(); ++it1) {
      // get the shorter shape's element (and set to 1 if there's no more)
      I elmt2 = (I)1;
      if (it2 != shape2.rend()) {
        elmt2 = *it2;
        ++it2;
      }
      I elmt1 = *it1;

      nsteps1.push_back(elmt1);
      nsteps2.push_back(elmt2);
      if (elmt1 == elmt2) {
        nrepeats1.push_back(1);
        nrepeats2.push_back(1);
      }
      else if ((elmt1 == 1) && (elmt2 != 1)) {
        nrepeats1.push_back(elmt2);
        nrepeats2.push_back(1);
      }
      else if ((elmt1 != 1) && (elmt2 == 1)) {
        nrepeats1.push_back(1);
        nrepeats2.push_back(elmt1);
      }
      else {
        throw std::runtime_error("The shape cannot be broadcasted.");
      }
    }
  }

  // partial template specialization for different views
  template <typename T, typename I>
  class BCastIterator<T,I,ContiguousView<I>,ContiguousView<I> > {
    // iterators
    StepBackIterator<T,I> sb1_;
    StepBackIterator<T,I> sb2_;
    T* itr_;
    I offset_;
    I sz_;

    public:
    // constructor
    BCastIterator(T* data1, const ContiguousView<I>& view1,
                  T* data2, const ContiguousView<I>& view2,
                  T* rdata, const ContiguousView<I>& viewr) {
      // get the nsteps and nrepeats
      std::vector<I> nsteps1, nsteps2;
      std::vector<I> nrepeats1, nrepeats2;
      _get_nsteps_nrepeats(view1.shape(), view2.shape(),
                           nsteps1, nsteps2, nrepeats1, nrepeats2);

      // set the default parameters
      sb1_ = StepBackIterator<T,I>(nsteps1, nrepeats1, data1);
      sb2_ = StepBackIterator<T,I>(nsteps2, nrepeats2, data2);
      itr_ = rdata;
      offset_ = 0;
      sz_ = viewr.size();
    }

    inline T& first() { return *sb1_; }
    inline T& second() { return *sb2_; }
    inline T& result() { return *itr_; }
    inline BCastIterator& operator++() {
      ++sb1_; ++sb2_; ++itr_; ++offset_;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
