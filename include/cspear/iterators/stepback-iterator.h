#ifndef CSPEAR_ITERATORS_STEPBACK_ITERATOR_H
#define CSPEAR_ITERATORS_STEPBACK_ITERATOR_H

#include <type_traits>
#include <vector>
#include <array>
#include <cspear/tools/assert.h>
#include <cspear/iterators/ewise-iterator.h>

namespace csp {
  /*
  StepBackIterator is an iterator where it repeatedly going through some
  area in the memory for some amount of times before proceeding to the next
  section. It is used in broadcasting iterator and reduce iterator.

  Example:
  * StepBackIterator({2}, {3}) means that every 2 steps, it will move back
    3 times before moving to the next section: 0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,...
  * StepBackIterator({2,4}, {3,5}) will do similar thing as before, but when
    it already proceeds 4 times, it will go back by (2*4) steps 5 times before
    it proceeds to the next section:
    0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,4,5,4,5, 6,7,6,7,6,7,
    0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,4,5,4,5, 6,7,6,7,6,7,
    0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,4,5,4,5, 6,7,6,7,6,7,
    0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,4,5,4,5, 6,7,6,7,6,7,
    0,1,0,1,0,1, 2,3,2,3,2,3, 4,5,4,5,4,5, 6,7,6,7,6,7,
    8,9,8,9,8,9, ...
  */
  template <typename T, typename I, typename View, bool keep_index=false,
            typename ArrType=std::vector<I> >
  class StepBackIterator {
    ArrType nsteps_orig_;
    ArrType nrepeats_orig_;
    ArrType ncounts_;
    ArrType nrepeats_;
    ArrType move_back_;
    // std::vector<I> nsteps_orig_ = {};
    // std::vector<I> nrepeats_orig_ = {};
    // std::vector<I> ncounts_ = {};
    // std::vector<I> nrepeats_ = {};
    // std::vector<I> move_back_ = {};
    EWiseIterator<T,I,View> it_;
    I idx_ = 0;

    public:
    StepBackIterator() {}
    StepBackIterator(const ArrType& nsteps,
                     const ArrType& nrepeats,
                     T* data, const View& view);
    // StepBackIterator(const std::vector<I>& nsteps,
    //                  const std::vector<I>& nrepeats,
    //                  T* data, const View& view);

    inline T& operator*() { return *it_; }
    inline I index() {
      static_assert(keep_index,
        "Internal error: obtaining index only available if keep_index is true");
      return idx_;
    }
    StepBackIterator& operator++();
  };
  template <typename I>
  I _get_move_back_stepback_iterator(
      std::vector<I>& ncounts, std::vector<I>& nrepeats,
      std::vector<I>& nsteps_orig, std::vector<I>& nrepeats_orig,
      std::vector<I>& move_back) {
    I i = 0;
    while (i < ncounts.size()) {
      --ncounts[i];
      if (ncounts[i] != 0) {
        return 0;
      }
      else {
        ncounts[i] = nsteps_orig[i];
        --nrepeats[i];
        if (nrepeats[i] != 0) {
          return move_back[i];
        }
        else {
          nrepeats[i] = nrepeats_orig[i];
          ++i;
        }
      }
    }
    return 0;
  }
  template <typename I>
  I _get_move_back_stepback_iterator(
      std::array<I,1>& ncounts, std::array<I,1>& nrepeats,
      std::array<I,1>& nsteps_orig, std::array<I,1>& nrepeats_orig,
      std::array<I,1>& move_back) {

    --ncounts[0];
    if (ncounts[0] != 0) {
      return 0;
    }
    else {
      ncounts[0] = nsteps_orig[0];
      --nrepeats[0];
      if (nrepeats[0] != 0) {
        return move_back[0];
      }
      else {
        nrepeats[0] = nrepeats_orig[0];
      }
    }
    return 0;
  }

  template <typename I>
  void _setup_move_back_stepback_iterator(std::vector<I>& move_back,
      const std::vector<I>& nsteps) {
    move_back = nsteps;
    for (I i = 1; i < move_back.size(); ++i) {
      move_back[i] *= move_back[i-1];
    }
  }
  template <typename I>
  void _setup_move_back_stepback_iterator(std::array<I,1>& move_back,
      const std::array<I,1>& nsteps) {
    move_back[0] = nsteps[0];
  }

  // implementations
  template <typename T, typename I, typename View, bool keep_index, typename ArrType>
  StepBackIterator<T,I,View,keep_index,ArrType>::StepBackIterator(
                   const ArrType& nsteps,
                   const ArrType& nrepeats, T* data, const View& view) :
    it_(data, view) {

    if (!EWiseIterator<T,I,View>::can_step_back) {
      _cspear_assert(false, "The view does not support reduce and broadcast. "
        "Please apply .copy() to get the contiguous copy of this view.");
    }
    // // the nsteps and nrepeats must have the same length
    // _cspear_assert(nsteps.size() == nrepeats.size(),
    // "The first and second argument of StepBackIterator must have the "
    // "same length");

    // make a copy from the argument
    nsteps_orig_ = nsteps;
    nrepeats_orig_ = nrepeats;
    ncounts_ = nsteps;
    nrepeats_ = nrepeats;
    // move_back_ = cummulative product(nsteps)
    _setup_move_back_stepback_iterator<I>(move_back_, nsteps);
  }

  template <typename T, typename I, typename View, bool keep_index, typename ArrType>
  StepBackIterator<T,I,View,keep_index,ArrType>&
  StepBackIterator<T,I,View,keep_index,ArrType>::operator++() {
    ++it_;
    if (keep_index) ++idx_;
    I mb = _get_move_back_stepback_iterator<I>(ncounts_, nrepeats_,
        nsteps_orig_, nrepeats_orig_, move_back_);
    if (mb > 0) {
      it_ -= mb;
      if (keep_index) idx_ -= mb;
    }
  }
}

#endif
