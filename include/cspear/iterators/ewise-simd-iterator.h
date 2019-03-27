#ifndef CSPEAR_ITERATORS_EWISE_SIMD_ITERATOR_H
#define CSPEAR_ITERATORS_EWISE_SIMD_ITERATOR_H

#include <cspear/views/contiguous-view.h>
#include <cspear/views/filter-view.h>
#include <cspear/simd/vector.h>

namespace csp {
  template <typename T, typename I, typename View>
  class EWiseSIMDIterator {
    public:
    static const bool is_implemented = false;

    // constructor
    EWiseSIMDIterator(T* data, const View& view);

    // iterator operator
    simd::Vector<T>& load(); // load the memory data into the intrinsic and return the intrinsic
    EWiseSIMDIterator& operator++();
    void store(); // store the intrinsic value to the memory data
    operator bool() const;
  };

  // partial template specialization for different views
  template <typename T, typename I>
  class EWiseSIMDIterator<T,I,ContiguousView<I> > {
    I sz_;
    T* data_;
    simd::Vector<T> vec_;
    I simd_sz_;
    I offset_;

    public:
    static const bool is_implemented = true;

    // constructor
    EWiseSIMDIterator(T* data, const ContiguousView<I>& view) {
      sz_ = view.size();
      data_ = data;
      offset_ = 0;
      simd_sz_ = vec_.size();
    }

    // iterator operator
    inline simd::Vector<T>& load() {
      if (sz_ >= offset_ + simd_sz_)
        return vec_.load(data_);
      else
        return vec_.partial_load(data_, sz_-offset_);
    }

    inline EWiseSIMDIterator& operator++() {
      data_ += simd_sz_;
      offset_ += simd_sz_;
      return *this;
    }

    inline void store() {
      if (sz_ >= offset_ + simd_sz_)
        vec_.store(data_);
      else
        vec_.partial_store(data_, sz_-offset_);
    }

    inline operator bool() const {
      return offset_ < sz_;
    }
  };
}

#endif
