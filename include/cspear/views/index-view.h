#ifndef CSPEAR_VIEWS_INDEX_VIEW_H
#define CSPEAR_VIEWS_INDEX_VIEW_H

#include <vector>
#include <type_traits>
#include <cspear/lib/idx.h>
#include <cspear/tools/types.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/array/array-forward-decl.h>

namespace csp {

  template <typename I>
  class IndexView {
    array<I> indices_ = {};

  public:
    IndexView() {}
    explicit IndexView(const array<I>& arr);

    void reshape(const std::vector<I>& shape);
    void reshape(std::initializer_list<I> shape);

    inline I size() const { return indices_.size(); }
    inline const std::vector<I>& shape() const { return indices_.shape(); }
    I idx(I i) const;

    inline const I* indices() const { return size() == 0 ? NULL : &indices_[0]; }
  };

  template <typename I>
  IndexView<I>::IndexView(const array<I>& arr) :
    indices_((I*)arr.data(), arr.view(), arr.dataptr()) {}

  template <typename I>
  inline void IndexView<I>::reshape(const std::vector<I>& shape) {
    indices_.reshape_(shape);
  }
  template <typename I>
  inline void IndexView<I>::reshape(std::initializer_list<I> shape) {
    indices_.reshape_(shape);
  }

  template <typename I>
  inline I IndexView<I>::idx(I i) const {
    return indices_[i];
  }
}

#endif
