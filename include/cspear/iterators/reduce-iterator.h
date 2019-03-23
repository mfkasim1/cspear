#ifndef CSPEAR_ITERATORS_REDUCE_ITERATOR_H
#define CSPEAR_ITERATORS_REDUCE_ITERATOR_H

#include <vector>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/iterators/stepback-iterator.h>

namespace csp {
  // reduce iterator
  // The result view must always be ContiguousView

  template <typename T, typename I, typename View>
  class ReduceIterator {
    public:
    static const bool is_implemented = false;

    // constructor
    ReduceIterator(const std::vector<I>& axes,
                   T* data1, const View& view1,
                   T* resdata, const ContiguousView<I>& viewr);

    // iterator operator
    T& first(); // reference to the element of the first data
    T& result(); // reference to the element of the result data
    ReduceIterator& operator++();
    operator bool() const;
  };

  // obtain the reduce output shape
  // (out.size() == 0) if it's invalid
  // the axes is assumed to be sorted
  template <typename I>
  std::vector<I> reduce_output_shape(const std::vector<I>& axes,
                                     const std::vector<I>& shape1) {
    std::vector<I> shaper;
    shaper.reserve(shape1.size());

    // iterate through the shape (if the i-th dimension is listed in axes,
    // then do not put it in the result's shape)
    auto it_axes = axes.begin();
    auto it1 = shape1.begin();
    for (I i = 0; i < shape1.size(); ++i, ++it1) {
      while ((it_axes != axes.end()) && (*it_axes < i)) {
        ++it_axes;
      }
      if ((it_axes == axes.end()) || (*it_axes != i)) {
        shaper.push_back(*it1);
      }
    }
    // if all axes are reduced, leave with one element
    if (shaper.size() == 0) {
      shaper.push_back(1);
    }
    return shaper;
  }

  template <typename I>
  void _get_nsteps_nrepeats_reduce(const std::vector<I>& axes,
                                   const std::vector<I>& shape1,
                                   std::vector<I>& nstepsr,
                                   std::vector<I>& nrepeatsr) {
    // nsteps and nrepeats would be the same size as axes
    nstepsr.reserve(axes.size());
    nrepeatsr.reserve(axes.size());

    I nstep = 1;
    auto its = shape1.rbegin();
    auto itx = axes.rbegin();
    for (I i = shape1.size()-1; i >= 0; --i, ++its) {
      if (itx == axes.rend()) break;
      if (i == *itx) {
        nstepsr.push_back(nstep);
        nrepeatsr.push_back(*its);
        ++itx;
        nstep = 1;
      }
      else {
        nstep *= *its;
      }
    }
  }

  // partial template specialization for different views
  template <typename T, typename I>
  class ReduceIterator<T,I,ContiguousView<I> > {
    // iterators
    T* it1_;
    StepBackIterator<T,I> sbr_;
    I offset_;
    I sz_;

    public:
    static const bool is_implemented = true;

    // constructor
    ReduceIterator(const std::vector<I>& axes,
                   T* data1, const ContiguousView<I>& view1,
                   T* rdata, const ContiguousView<I>& viewr) {
      // get the nsteps and nrepeats
      std::vector<I> nstepsr;
      std::vector<I> nrepeatsr;
      _get_nsteps_nrepeats_reduce(axes, view1.shape(),
                                  nstepsr, nrepeatsr);

      // set the default parameters
      sbr_ = StepBackIterator<T,I>(nstepsr, nrepeatsr, rdata);
      it1_ = data1;
      offset_ = 0;
      sz_ = view1.size();
    }

    inline T& first() { return *it1_; }
    inline T& result() { return *sbr_; }
    inline ReduceIterator& operator++() {
      ++sbr_; ++it1_; ++offset_;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
