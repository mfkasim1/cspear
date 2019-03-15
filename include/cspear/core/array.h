#ifndef CSPEAR_CORE_ARRAY_H
#define CSPEAR_CORE_ARRAY_H

#include <vector>
#include <initializer_list>
#include <cspear/core/utils.h>
#include <cspear/tools/types.h>

namespace csp {
  template <typename T, typename I=tools::Int>
  class array {
    T* data_;
    I sz_; // total number of elements
    std::vector<I> shape_;
    bool allocated_; // flag to indicate if the data is allocated by us

  public:
    // constructors and destructor
    array();
    array(std::initializer_list<T> elmts);
    array(const T* a, I sz);
    array(const T* a, std::initializer_list<I> shape);
    array(const array<T,I>& a);
    ~array();

    // indexing
    T& operator[](I idx) { return data_[idx]; }

    // assignment operator and copy
    array<T,I>& operator=(const array<T,I>& a);
    array<T,I> copy() const;

    // parameters
    T* data() { return data_; }
    const T* data() const { return data_; }
    I size() const { return sz_; }
    I ndim() const { return shape_.size(); }
    const std::vector<I>& shape() const { return shape_; }

    // casting and device movement
    template <typename T2> array<T2,I> astype() const;

    // reshape and resize
    array<T,I>& resize(I sz);
    array<T,I>& reshape(std::initializer_list<I> shape);

  private:
    void _realloc();
  };
}

#endif
