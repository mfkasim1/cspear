#ifndef CSPEAR_VIEWS_CONTIGUOUS_VIEW_H
#define CSPEAR_VIEWS_CONTIGUOUS_VIEW_H

#include <vector>

namespace csp {
  template <typename I>
  class ContiguousView {
    std::vector<I> shape_;
    I sz_;

    public:
    ContiguousView();
    ContiguousView(const std::vector<I>& shape);
    ContiguousView(std::initializer_list<I> shape);

    void reshape(const std::vector<I>& shape);
    void reshape(std::initializer_list<I> shape);
    I size() const;
    const std::vector<I>& shape() const;
    I idx(I i) const;

    private:
    static I _compute_size(const std::vector<I>& shape);
  };

  // implementations
  template <typename I>
  ContiguousView<I>::ContiguousView() {}

  template <typename I>
  ContiguousView<I>::ContiguousView(const std::vector<I>& shape) {
    reshape(shape);
  }

  template <typename I>
  ContiguousView<I>::ContiguousView(std::initializer_list<I> shape) {
    reshape(shape);
  }

  template <typename I>
  inline void ContiguousView<I>::reshape(const std::vector<I>& shape) {
    shape_ = shape;
    sz_ = _compute_size(shape_);
  }

  template <typename I>
  inline void ContiguousView<I>::reshape(std::initializer_list<I> shape) {
    shape_ = shape;
    sz_ = _compute_size(shape_);
  }

  template <typename I>
  inline I ContiguousView<I>::size() const {
    return sz_;
  }

  template <typename I>
  inline const std::vector<I>& ContiguousView<I>::shape() const {
    return shape_;
  }

  template <typename I>
  inline I ContiguousView<I>::idx(I i) const {
    return i;
  }

  template <typename I>
  inline I ContiguousView<I>::_compute_size(const std::vector<I>& shape) {
    I sz = 1;
    for (auto& s : shape) {
      sz *= s;
    }
    return sz;
  }
}

#endif
