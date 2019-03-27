#ifndef CSPEAR_SIMD_TYPES_H
#define CSPEAR_SIMD_TYPES_H

#if defined(__AVX512__)
  #include <cspear/simd/vector-avx.h>
  #define __SIMD__
#endif

#if defined(__AVX__)
  #include <cspear/simd/vector-avx.h>
  #define __SIMD__
#endif

namespace csp {
  namespace simd {
    #if defined(__AVX512__)
      #define __SIMD_AVX512__
      template <typename T> using Vector = VectorAVX512<T>;
    #elif defined(__AVX__)
      #define __SIMD_AVX__
      template <typename T> using Vector = VectorAVX<T>;
    #endif
  }
}

#endif
