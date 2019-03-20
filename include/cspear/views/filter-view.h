#ifndef CSPEAR_VIEWS_FILTER_VIEW_H
#define CSPEAR_VIEWS_FILTER_VIEW_H

#include <iostream>
#include <vector>
#include <cspear/views/contiguous-view.h>

namespace csp {
  template <typename I>
  class FilterView : public ContiguousView<I> {
    std::vector<I> shape_;
    I sz_;
    std::vector<I> idxs_;

    public:
    FilterView() {}
    FilterView(const bool* filter, const I sz);

    void reshape(const std::vector<I>& shape);
    void reshape(std::initializer_list<I> shape);
    I size() const;
    const std::vector<I>& shape() const;
    I idx(I i) const;
    const I* idxs() const;

    private:
    void _get_indices(const bool* a, const I sz);
  };

  // implementations
  template <typename I>
  FilterView<I>::FilterView(const bool* filter, const I sz) {
    _get_indices(filter, sz);
    sz_ = idxs_.size();
    shape_ = {sz_};
  }

  template <typename I>
  inline void FilterView<I>::reshape(const std::vector<I>& shape) {
    ContiguousView<I>::reshape(shape);
  }

  template <typename I>
  inline void FilterView<I>::reshape(std::initializer_list<I> shape) {
    ContiguousView<I>::reshape(shape);
  }

  template <typename I>
  inline I FilterView<I>::size() const {
    return sz_;
  }

  template <typename I>
  inline const std::vector<I>& FilterView<I>::shape() const {
    return shape_;
  }

  template <typename I>
  inline I FilterView<I>::idx(I i) const {
    return idxs_[i];
  }

  template <typename I>
  inline const I* FilterView<I>::idxs() const {
    return &idxs_[0];
  }

  template <typename I>
  inline void FilterView<I>::_get_indices(const bool* a, const I sz) {
    idxs_.reserve(sz);

    for (I i = 0; i < sz; ++i) {
      if (a[i]) idxs_.push_back(i);
    }
  }
}

#endif
