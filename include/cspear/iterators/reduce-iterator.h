#ifndef CSPEAR_ITERATORS_REDUCE_ITERATOR_H
#define CSPEAR_ITERATORS_REDUCE_ITERATOR_H

#include <type_traits>
#include <vector>
#include <array>
#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/iterators/stepback-iterator.h>
#include <cspear/iterators/ewise-iterator.h>

namespace csp {
  // reduce iterator
  // The result view must always be ContiguousView

  // obtain the reduce output shape
  // (out.size() == 0) if it's invalid
  // the axes is assumed to be sorted
  template <typename I, typename ArrType>
  std::vector<I> reduce_output_shape(const ArrType& axes,
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
  void _resize_arrtype(std::array<I,1>& arr, I n) {}
  template <typename I>
  void _resize_arrtype(std::vector<I>& arr, I n) {
    arr.resize(n);
  }

  template <typename I, typename ArrType>
  void _get_nsteps_nrepeats_reduce(const ArrType& axes,
                                   const std::vector<I>& shape1,
                                   ArrType& nstepsr,
                                   ArrType& nrepeatsr) {
    // nsteps and nrepeats would be the same size as axes
    I nsize = axes.size();
    _resize_arrtype(nstepsr, nsize);
    _resize_arrtype(nrepeatsr, nsize);

    I nstep = 1;
    auto its = shape1.rbegin();
    auto itx = axes.rbegin();
    I j = 0;
    for (I i = shape1.size()-1; i >= 0; --i, ++its) {
      if (itx == axes.rend()) break;
      if (i == *itx) {
        nstepsr[j] = nstep;
        nrepeatsr[j] = *its;
        ++j;
        ++itx;
        nstep = 1;
      }
      else {
        nstep *= *its;
      }
    }
  }

  // partial template specialization for different views
  template <typename T, typename I, typename View,
            bool keep_index=false, // to keep the index of the given axis
            typename ArrType=std::vector<I> >
  class ReduceIterator {
    // iterators
    EWiseIterator<T,I,View> it1_;
    StepBackIterator<T,I,ContiguousView<I>,keep_index,ArrType> sbr_;
    I remaining_;

    // keep index properties
    I idx_; // idx of it1_ at the given axis
    I nrepeat_times_orig_;
    I nmoveback_after_orig_;
    I nrepeat_times_;
    I nmoveback_after_;

    public:
    static const bool is_implemented = true;

    // constructor
    ReduceIterator(const ArrType& axes,
                   T* data1, const View& view1,
                   T* rdata, const ContiguousView<I>& viewr) :
      it1_(data1, view1),
      remaining_(view1.size()) {

      if (keep_index) {
        _cspear_assert(axes.size() == 1,
                       "Internal error: cannot keep index in multiple axes.");
        I ax = axes[0];
        auto& shape = view1.shape();
        nrepeat_times_orig_ = 1;
        nmoveback_after_orig_ = 1;
        for (I sax = shape.size()-1; sax > ax; --sax) {
          auto s = shape[sax];
          nrepeat_times_orig_ *= s;
          nmoveback_after_orig_ *= s;
        }
        nmoveback_after_orig_ *= shape[ax];
        nmoveback_after_ = nmoveback_after_orig_;
        nrepeat_times_ = nrepeat_times_orig_;
        idx_ = 0;
        // (2,3,4), ax = 0
        // repeat 3*4=12 times, moveback after 2*3*4 times -> ({1},{12})
        // 0,0,0,0, 0,0,0,0, 0,0,0,0,
        // 1,1,1,1, 1,1,1,1, 1,1,1,1, ...
        //
        // (2,3,4), ax = 1
        // repeat 4 times, moveback after 3*4 times
        // 0,0,0,0, 1,1,1,1, 2,2,2,2,
        // 0,0,0,0, 1,1,1,1, 2,2,2,2, ...
        //
        // (2,3,4), ax = 2
        // repeat 1 time, moveback after 4 times
        // 0,1,2,3, 0,1,2,3, 0,1,2,3, ... -> ({4} , {})
      }

      // get the nsteps and nrepeats
      ArrType nstepsr;
      ArrType nrepeatsr;
      _get_nsteps_nrepeats_reduce(axes, view1.shape(),
                                  nstepsr, nrepeatsr);

      // set the default parameters
      sbr_ = StepBackIterator<T,I,ContiguousView<I>,keep_index,ArrType>(
        nstepsr, nrepeatsr, rdata, viewr);
    }

    inline T& first() { return *it1_; }
    inline T& result() { return *sbr_; }
    inline I result_index() {
      static_assert(keep_index,
        "Internal error: obtaining index only available if keep_index is true");
      return sbr_.index();
    }
    inline I first_index() {
      static_assert(keep_index,
        "Internal error: obtaining index only available if keep_index is true");
      return idx_;
    }
    inline ReduceIterator& operator++() {
      ++sbr_; ++it1_; --remaining_;

      // update the index, if needed
      if (keep_index) {
        --nrepeat_times_;
        --nmoveback_after_;
        if (nrepeat_times_ == 0) {
          ++idx_;
          nrepeat_times_ = nrepeat_times_orig_;
        }
        if (nmoveback_after_ == 0) {
          idx_ = 0;
          nmoveback_after_ = nmoveback_after_orig_;
        }
      }
    }

    inline operator bool() const {
      return remaining_ > 0;
    }
  };
}

#endif
