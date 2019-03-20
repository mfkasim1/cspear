#ifndef CSPEAR_VIEWS_FILTER_VIEW_H
#define CSPEAR_VIEWS_FILTER_VIEW_H

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
    array<bool,I,ContiguousView> filter_;

    public:
    FilterView(array<bool,I,ContiguousView>&& filter);
    FilterView(const array<bool,I,ContiguousView>& filter);

    void reshape(const std::vector<I>& shape);
    void reshape(std::initializer_list<I> shape);
    I size() const;
    const std::vector<I>& shape() const;
    const array<bool,I,ContiguousView>& filter() const;
  };

  // implementations
  template <typename I>
  FilterView<I>::FilterView(array<bool,I,ContiguousView>&& filter) {
    filter_ = filter;
  }

  template <typename I>
  FilterView<I>::FilterView(const array<bool,I,ContiguousView>& filter) {
    filter_ = filter;
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
  inline const array<bool,I,ContiguousView>& FilterView<I>::filter() const {
    return filter_;
  }
}

#endif
