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
  #define __SIMD__ 0
#endif

namespace csp {
  namespace simd {
    #if defined(__AVX512__)
      #define __SIMD_AVX512__
      template <typename T> using Vector = VectorAVX512<T>;
    #elif defined(__AVX__)
      #define __SIMD_AVX__
      template <typename T> using Vector = VectorAVX<T>;
    #else
      template <typename T> using Vector = std::vector<T>;
    #endif
  }
}

#endif
