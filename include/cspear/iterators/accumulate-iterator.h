#ifndef CSPEAR_ITERATORS_ACCUMULATE_ITERATOR_H
#define CSPEAR_ITERATORS_ACCUMULATE_ITERATOR_H

#include <vector>
#include <cspear/views/contiguous-view.h>
#include <cspear/iterators/reduce-iterator.h>

namespace csp {
  // Accumulate iterator
  // The result view must always be ContiguousView

  template <typename T, typename I, typename View>
  class AccumulateIterator {
    public:
    static const bool is_implemented = false;

    // constructor
    AccumulateIterator(I ax, T initval,
                   T* data1, const View& view1,
                   T* resdata, const ContiguousView<I>& viewr);

    // iterator operator
    T& first(); // reference to the element of the first data
    T& prev(); // reference to the result array to be operated with first()
    T& result(); // reference to the element of the result data
    AccumulateIterator& operator++();
    operator bool() const;
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class AccumulateIterator<T,I,ContiguousView<I> > {
    T* it1_ = NULL;
    T* itr_ = NULL;
    T* itrprev_ = NULL;
    T initval_ = 0;
    I offset_ = 0;
    I sz_ = 0;
    I count_to_disappear_ = 0;

    I delta_ = 1; // separation between itr and itrprev
    I disappear_every_ = 1;
    bool isappear_ = false;

    public:
    static const bool is_implemented = true;

    // constructor
    AccumulateIterator(I ax, T initval,
                   T* data1, const ContiguousView<I>& view1,
                   T* rdata, const ContiguousView<I>& viewr) :
      it1_(data1),
      itr_(rdata),
      itrprev_(rdata),
      initval_(initval) {

      offset_ = 0;
      sz_ = view1.size();

      // get the separation of the pointers
      auto& shape = view1.shape();
      delta_ = 1;
      disappear_every_ = shape[ax];
      for (I i = ax+1; i < shape.size(); ++i) {
        auto& si = shape[i];
        delta_ *= si;
        disappear_every_ *= si;
      }

      // reset the counters
      count_to_disappear_ = 0;
    }

    inline T& first() { return *it1_; }
    inline T& prev() {
      if (count_to_disappear_ >= delta_)
        return *itrprev_;
      else
        return initval_;
    }
    inline T& result() { return *itr_; }
    inline AccumulateIterator& operator++() {
      ++it1_; ++itr_;
      ++offset_;

      ++count_to_disappear_;
      if (count_to_disappear_ == disappear_every_) {
        count_to_disappear_ = 0;
      }

      // move the lagging pointer
      if (offset_ > delta_) {
        ++itrprev_;
      }
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
