#ifndef CSPEAR_LIB_IDX_H
#define CSPEAR_LIB_IDX_H

#include <vector>
#include <initializer_list>

namespace csp {
  template <typename I, typename Vec>
  I ravel_index(const Vec& idxs, const std::vector<I>& dims) {
    // ravel indices
    I idx = 0;
    I stride = 1;
    auto its = dims.rbegin();
    auto it = idxs.end() - 1;
    for (; its != dims.rend(); --it, ++its) {
      auto& i = *it;
      _cspear_assert(i >= 0 && i < *its, "Index out-of-bounds");

      idx += i * stride;
      stride *= (*its);
    }
    return idx;
  }

  template <typename I>
  std::vector<I> unravel_index(I idx, const std::vector<I>& dims) {
    I ndims = dims.size();
    std::vector<I> res(ndims);
    if (ndims == 0) return res;

    // get the size
    I size = 1;
    for (auto& d : dims) size *= d;

    for (I i = 0; i < ndims; ++i) {
      size /= dims[i];
      res[i] = idx / size;
      idx = idx % size;
    }
    return res;
  }
}

#endif
