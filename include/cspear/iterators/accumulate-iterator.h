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
    AccumulateIterator(I ax,
                   T* data1, const View& view1,
                   T* resdata, const ContiguousView<I>& viewr,
                   T* tempdata, const ContiguousView<I>& viewt);

    // iterator operator
    T& first(); // reference to the element of the first data
    T& reducetemp(); // reference to the temporary reduced array data
    T& result(); // reference to the element of the result data
    AccumulateIterator& operator++();
    operator bool() const;
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class AccumulateIterator<T,I,ContiguousView<I> > {
    ReduceIterator<T,I,ContiguousView<I> > rit_;
    T* itr_ = NULL;

    public:
    static const bool is_implemented = true;

    // constructor
    AccumulateIterator(I ax,
                   T* data1, const ContiguousView<I>& view1,
                   T* rdata, const ContiguousView<I>& viewr,
                   T* tdata, const ContiguousView<I>& viewt) :
      rit_({ax}, data1, view1, tdata, viewt) {
      itr_ = rdata;
    }

    inline T& first() { return rit_.first(); }
    inline T& reducetemp() { return rit_.result(); }
    inline T& result() { return *itr_; }
    inline AccumulateIterator& operator++() {
      ++rit_; ++itr_;
    }

    inline operator bool() const {
      return bool(rit_);
    }
  };
}

#endif
