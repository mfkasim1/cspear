#ifndef CSPEAR_SIMD_TYPES_H
#define CSPEAR_SIMD_TYPES_H

#include <vector>

#if defined(__AVX512__)
  #include <cspear/simd/vector-avx.h>
  #ifndef __SIMD__
    #define __SIMD__ 1
  #endif
#endif

#if defined(__AVX__)
  #include <cspear/simd/vector-avx.h>
  #ifndef __SIMD__
    #define __SIMD__ 1
  #endif
#endif

#ifndef __SIMD__
  #include <cspear/simd/vector-dummy.h>
  #define __SIMD__ 0
#endif

namespace csp {
  namespace simd {
    #if defined(__AVX512__)
      #define __SIMD_AVX512__
      template <typename T> using Vector = VectorAVX512<T>;
      #define SIMD_ALIGNMENT 64
    #elif defined(__AVX__)
      #define __SIMD_AVX__
      template <typename T> using Vector = VectorAVX<T>;
      #define SIMD_ALIGNMENT 32
    #else
      template <typename T> using Vector = VectorDummy<T>;
    #endif
  }
}

#endif
