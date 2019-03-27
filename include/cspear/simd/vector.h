#ifndef CSPEAR_SIMD_TYPES_H
#define CSPEAR_SIMD_TYPES_H

#if defined(__AVX2__)
  #include <cspear/simd/vector-avx.h>
  #define __SIMD__ 1
  #define __SIMD_AVX2__
#elif defined(__AVX__)
  #include <cspear/simd/vector-avx.h>
  #define __SIMD__ 1
  #define __SIMD_AVX__
#endif

#endif
