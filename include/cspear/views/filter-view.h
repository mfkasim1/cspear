#ifndef CSPEAR_VIEWS_FILTER_VIEW_H
#define CSPEAR_VIEWS_FILTER_VIEW_H

#include <iostream>
#include <vector>
#include <cspear/views/contiguous-view.h>

namespace csp {
  // forward declaration of array
  template <typename T, typename I, template<typename> typename View>
  class array;

  template <typename I>
  class FilterView : public ContiguousView<I> {
    std::vector<I> shape_;
    I sz_;
    std::vector<I> idxs_;

    public:
    FilterView() {}
    FilterView(array<bool,I,ContiguousView>&& filter);
    FilterView(const array<bool,I,ContiguousView>& filter);

    void reshape(const std::vector<I>& shape);
    void reshape(std::initializer_list<I> shape);
    I size() const;
    const std::vector<I>& shape() const;
    I idx(I i) const;
    const I* idxs() const;

    private:
    void _get_indices(const array<bool,I,ContiguousView>& filter);
  };

  // implementations
  template <typename I>
  FilterView<I>::FilterView(array<bool,I,ContiguousView>&& filter) {
    _get_indices(filter);
    sz_ = idxs_.size();
    shape_ = {sz_};
  }

  template <typename I>
  FilterView<I>::FilterView(const array<bool,I,ContiguousView>& filter) {
    _get_indices(filter);
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
    return &idxs_[0]; //.begin();
  }

  template <typename I>
  inline void FilterView<I>::_get_indices(const array<bool,I,ContiguousView>& a) {
    idxs_.reserve(a.size());

    for (I i = 0; i < a.size(); ++i) {
      if (a[i]) idxs_.push_back(i);
    }
  }
}

#endif
