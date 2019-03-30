#ifndef CSPEAR_ITERATORS_EWISE_ITERATOR_H
#define CSPEAR_ITERATORS_EWISE_ITERATOR_H

#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>

namespace csp {
  template <typename T, typename I, typename View>
  class EWiseIterator {
    public:
    // constructor
    EWiseIterator(T* data, const View& view);

    // iterator operator
    T& operator*();
    EWiseIterator& operator++();
    operator bool() const;

    // indexing
    I idx(I i);
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class EWiseIterator<T,I,ContiguousView<I> > {
    I sz_;
    T* data_;
    I offset_;

    public:
    // constructor
    EWiseIterator(T* data, const ContiguousView<I>& view) {
      sz_ = view.size();
      data_ = data;
      offset_ = 0;
    }

    // iterator operator
    inline T& operator*() {
      return *data_;
    }

    inline EWiseIterator& operator++() {
      data_++;
      offset_++;
      return *this;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };

  template <typename T, typename I>
  class EWiseIterator<T,I,FilterView<I> > {
    I sz_;
    T* data_;
    T* origin_data_;
    I offset_;
    const I* all_idxs_;
    const I* idxs_;

    public:
    EWiseIterator(T* data, const FilterView<I>& view) {
      sz_ = view.size();
      origin_data_ = data;
      offset_ = 0;
      idxs_ = view.idxs();
      all_idxs_ = idxs_;
      if (sz_ == 0)
        data_ = NULL;
      else
        data_ = &origin_data_[*idxs_];
    }

    // iterator operator
    inline T& operator*() {
      return *data_;
    }

    inline EWiseIterator& operator++() {
      idxs_++;
      offset_++;
      data_ = &origin_data_[*idxs_];
      return *this;
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
