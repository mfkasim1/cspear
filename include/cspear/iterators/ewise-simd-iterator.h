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
    using VectorDataType = simd::Vector<T>;

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
    I sz_ = 0;
    T* data_ = NULL;
    simd::Vector<T> vec_;
    I simd_sz_ = 0;
    I remaining_ = 0;
    // bool is_aligned_ = false;

    public:
    static const bool is_implemented = true;
    using VectorDataType = simd::Vector<T>;

    // constructor
    EWiseSIMDIterator(T* data, const ContiguousView<I>& view) {
      sz_ = view.size();
      data_ = data;
      remaining_ = sz_;
      simd_sz_ = vec_.size();
      // #if (__SIMD__ == 1)
      // is_aligned_ = ((unsigned long)data & (SIMD_ALIGNMENT-1) == 0);
      // #endif
    }

    // iterator operator
    inline simd::Vector<T>& load() {
      if (remaining_ < simd_sz_)
        return vec_.partial_load(data_, remaining_);
      // else if (is_aligned_)
      //   return vec_.loada(data_);
      else
        return vec_.load(data_);
    }

    inline EWiseSIMDIterator& operator++() {
      data_ += simd_sz_;
      remaining_ -= simd_sz_;
      return *this;
    }

    inline void store() {
      if (remaining_ < simd_sz_)
        vec_.partial_store(data_, remaining_);
      // else if (is_aligned_)
      //   vec_.storea(data_);
      else
        vec_.store(data_);
    }

    inline operator bool() const {
      return remaining_ > 0;
    }
  };
}

#endif
