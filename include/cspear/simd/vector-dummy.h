#ifndef CSPEAR_AVX_VECTOR_DUMMY_H
#define CSPEAR_AVX_VECTOR_DUMMY_H

#include <type_traits>
#include <immintrin.h>

#include <cstdint>
#include <initializer_list>
#include <cspear/tools/assert.h>

namespace csp {
  namespace simd {
    // dummy simd vector class, just to make it compiled, but it should never
    // be called
    template <typename T>
    class VectorDummy {
      public:
      static const bool is_implemented = false;

      VectorDummy() {
        _cspear_assert(false, "This vector dummy should not be called. "
                       "Please report this error to the developer.");
      }
      VectorDummy(T a) {
        _cspear_assert(false, "This vector dummy should not be called. "
                       "Please report this error to the developer.");
      }

      // loada
      VectorDummy& loada(const T* dat) {};
      VectorDummy& load(const T* dat) {}; // unaligned
      VectorDummy& partial_load(const T* dat, int n) {};

      // parameters
      int size() {};
      // inline SimdType& data() {};
      // inline const SimdType& data() const {};

      // storing
      VectorDummy& storea(T* dat) {};
      VectorDummy& store(T* dat) {}; // unaligned
      VectorDummy& partial_store(T* dat, int n) {};

      // arithmetic operators
      VectorDummy operator-() const {};
      VectorDummy operator+(const VectorDummy& other) const {};
      VectorDummy operator-(const VectorDummy& other) const {};
      VectorDummy operator*(const VectorDummy& other) const {};
      VectorDummy operator/(const VectorDummy& other) const {};
      VectorDummy& operator+=(const VectorDummy& other) {};
      VectorDummy& operator-=(const VectorDummy& other) {};
      VectorDummy& operator*=(const VectorDummy& other) {};
      VectorDummy& operator/=(const VectorDummy& other) {};
      VectorDummy& operator=(const VectorDummy& other) {};
    };
  }
}

#endif
