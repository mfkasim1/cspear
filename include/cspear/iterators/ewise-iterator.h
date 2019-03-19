#ifndef CSPEAR_ITERATORS_EWISE_ITERATOR_H
#define CSPEAR_ITERATORS_EWISE_ITERATOR_H

#include <cspear/views/contiguous-view.h>

namespace csp {
  template <typename T, typename I, template<typename> typename View>
  class EWiseIterator {
    public:
    // constructor
    EWiseIterator(T* data, const View<I>& view);

    // iterator operator
    T& operator*();
    EWiseIterator& operator++();
    operator bool() const;

    // indexing
    I idx(I i);
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class EWiseIterator<T,I,ContiguousView> {
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

    inline I idx(I i) {
      return i;
    }
  };
}

#endif
