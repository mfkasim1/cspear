#ifndef CSPEAR_ITERATORS_STEPBACK_ITERATOR_H
#define CSPEAR_ITERATORS_STEPBACK_ITERATOR_H

#include <vector>
#include <cspear/tools/assert.h>

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
  template <typename T, typename I>
  class StepBackIterator {
    std::vector<I> nsteps_orig_;
    std::vector<I> nrepeats_orig_;
    std::vector<I> ncounts_;
    std::vector<I> nrepeats_;
    std::vector<I> move_back_;
    T* ptr_;

    public:
    StepBackIterator() {}
    StepBackIterator(const std::vector<I>& nsteps,
                     const std::vector<I>& nrepeats, T* ptr);

    inline T& operator*() { return *ptr_; }
    StepBackIterator& operator++();

    private:
    I _get_move_back();
  };

  // implementations

  template <typename T, typename I>
  StepBackIterator<T,I>::StepBackIterator(const std::vector<I>& nsteps,
                   const std::vector<I>& nrepeats, T* ptr) {
    // the nsteps and nrepeats must have the same length
    _cspear_assert(nsteps.size() == nrepeats.size(),
    "The first and second argument of StepBackIterator must have the "
    "same length");

    // make a copy from the argument
    nsteps_orig_ = nsteps;
    nrepeats_orig_ = nrepeats;
    ncounts_ = nsteps;
    nrepeats_ = nrepeats;
    ptr_ = ptr;
    // move_back_ = cummulative product(nsteps)
    move_back_ = nsteps;
    for (I i = 1; i < move_back_.size(); ++i) {
      move_back_[i] *= move_back_[i-1];
    }
  }

  template <typename T, typename I>
  StepBackIterator<T,I>& StepBackIterator<T,I>::operator++() {
    ++ptr_;
    I mb = _get_move_back();
    if (mb > 0) {
      ptr_ -= mb;
    }
  }

  template <typename T, typename I>
  I StepBackIterator<T,I>::_get_move_back() {
    I i = 0;
    while (i < ncounts_.size()) {
      --ncounts_[i];
      if (ncounts_[i] != 0) {
        return 0;
      }
      else {
        ncounts_[i] = nsteps_orig_[i];
        --nrepeats_[i];
        if (nrepeats_[i] != 0) {
          return move_back_[i];
        }
        else {
          nrepeats_[i] = nrepeats_orig_[i];
          ++i;
        }
      }
    }
    return 0;
  }
}

#endif