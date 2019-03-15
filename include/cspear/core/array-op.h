#ifndef CSPEAR_CORE_ARRAY_OP_H
#define CSPEAR_CORE_ARRAY_OP_H

#include <cspear/core/array.h>
#include <cspear/tools/assert.h>

namespace csp {
  // unary operations
  template <typename T, typename I>
  array<T,I> array<T,I>::operator-() {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = -data_[i];
    }
    return res;
  }

  // binary operations
  template <typename T, typename I>
  array<T,I> array<T,I>::operator+(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] + a.data_[i];
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator-(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] - a.data_[i];
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator*(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] * a.data_[i];
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator/(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] / a.data_[i];
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator+(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] + a;
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator-(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] - a;
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator*(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] * a;
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::operator/(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = data_[i] / a;
    }
    return res;
  }
  template <typename T, typename I>
  array<T,I> array<T,I>::rdiv(T a) {
    array<T,I> res;
    res.resize(sz_);
    for (I i = 0; i < sz_; ++i) {
      res.data_[i] = a / data_[i];
    }
    return res;
  }

  // binary operations (inplace)
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator+=(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    for (I i = 0; i < sz_; ++i) {
      data_[i] += a.data_[i];
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator-=(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    for (I i = 0; i < sz_; ++i) {
      data_[i] -= a.data_[i];
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator*=(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    for (I i = 0; i < sz_; ++i) {
      data_[i] *= a.data_[i];
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator/=(const array<T,I>& a) {
    _cspear_assert(sz_ == a.size(), "The operand must have the same size.");
    _cspear_assert(shape_ == a.shape_, "The operand must have the same shape.");

    for (I i = 0; i < sz_; ++i) {
      data_[i] /= a.data_[i];
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator+=(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] += a;
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator-=(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] -= a;
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator*=(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] *= a;
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::operator/=(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] /= a;
    }
    return *this;
  }
  template <typename T, typename I>
  array<T,I>& array<T,I>::rdiv_(T a) {
    for (I i = 0; i < sz_; ++i) {
      data_[i] = a / data_[i];
    }
    return *this;
  }
}

#endif
