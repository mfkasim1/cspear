#ifndef CSPEAR_AVX_AVX_H
#define CSPEAR_AVX_AVX_H

#include <type_traits>
#include <immintrin.h>


#define AVX_DOUBLE_SIZE 4
#define AVX_SINGLE_SIZE 8

#include <cstdint>
#include <initializer_list>
#include <cspear/tools/assert.h>

namespace csp {
  namespace simd {
    __m256i avx_mask8(int n) {
      const int f = 0xFFFFFFFF;
      switch(n) {
        case 0:
          return _mm256_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0);
        case 1:
          return _mm256_setr_epi32(f, 0, 0, 0, 0, 0, 0, 0);
        case 2:
          return _mm256_setr_epi32(f, f, 0, 0, 0, 0, 0, 0);
        case 3:
          return _mm256_setr_epi32(f, f, f, 0, 0, 0, 0, 0);
        case 4:
          return _mm256_setr_epi32(f, f, f, f, 0, 0, 0, 0);
        case 5:
          return _mm256_setr_epi32(f, f, f, f, f, 0, 0, 0);
        case 6:
          return _mm256_setr_epi32(f, f, f, f, f, f, 0, 0);
        case 7:
          return _mm256_setr_epi32(f, f, f, f, f, f, f, 0);
        case 8:
          return _mm256_setr_epi32(f, f, f, f, f, f, f, f);
        default:
          return _mm256_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0);
      }
    }
    __m256i avx_mask4(int n) {
      const std::int64_t f = 0xFFFFFFFFFFFFFFFF;
      switch(n) {
        case 0:
          return _mm256_setr_epi64x(0, 0, 0, 0);
        case 1:
          return _mm256_setr_epi64x(f, 0, 0, 0);
        case 2:
          return _mm256_setr_epi64x(f, f, 0, 0);
        case 3:
          return _mm256_setr_epi64x(f, f, f, 0);
        case 4:
          return _mm256_setr_epi64x(f, f, f, f);
        default:
          return _mm256_setr_epi64x(0, 0, 0, 0);
      }
    }

    template <typename T>
    class VectorAVX {

      public:
      using SimdType = typename std::conditional<std::is_same<T,double>::value,
            __m256d, __m256>::type;
      static const bool is_implemented;
      private:
      SimdType a_;

      public:
      VectorAVX() {}
      VectorAVX(SimdType&& a);
      VectorAVX(T value);
      VectorAVX(std::initializer_list<T> values);
      VectorAVX(const VectorAVX& other) { a_ = other.a_; }

      // loada
      VectorAVX& loada(const T* dat);
      VectorAVX& load(const T* dat); // unaligned
      VectorAVX& partial_load(const T* dat, int n);

      // parameters
      int size();
      inline SimdType& data() { return a_; }
      inline const SimdType& data() const { return a_; }

      // storing
      VectorAVX& storea(T* dat);
      VectorAVX& store(T* dat); // unaligned
      VectorAVX& partial_store(T* dat, int n);

      // arithmetic operators
      VectorAVX operator-() const;
      VectorAVX operator+(const VectorAVX& other) const;
      VectorAVX operator-(const VectorAVX& other) const;
      VectorAVX operator*(const VectorAVX& other) const;
      VectorAVX operator/(const VectorAVX& other) const;
      VectorAVX max(const VectorAVX& other) const;
      VectorAVX min(const VectorAVX& other) const;
      VectorAVX& operator+=(const VectorAVX& other);
      VectorAVX& operator-=(const VectorAVX& other);
      VectorAVX& operator*=(const VectorAVX& other);
      VectorAVX& operator/=(const VectorAVX& other);
      VectorAVX& operator=(const VectorAVX& other);
    };

    // implementation status
    template <> const bool VectorAVX<std::uint8_t>::is_implemented = false;
    template <> const bool VectorAVX<std::uint16_t>::is_implemented = false;
    template <> const bool VectorAVX<std::uint32_t>::is_implemented = false;
    template <> const bool VectorAVX<std::uint64_t>::is_implemented = false;
    template <> const bool VectorAVX<std::int8_t>::is_implemented = false;
    template <> const bool VectorAVX<std::int16_t>::is_implemented = false;
    template <> const bool VectorAVX<std::int32_t>::is_implemented = false;
    template <> const bool VectorAVX<std::int64_t>::is_implemented = false;
    template <> const bool VectorAVX<bool>::is_implemented = false;
    template <> const bool VectorAVX<float>::is_implemented = true;
    template <> const bool VectorAVX<double>::is_implemented = true;

    // implementations in double
    template <> inline VectorAVX<double>::VectorAVX(std::initializer_list<double> values) {
      _cspear_assert(values.size() == AVX_DOUBLE_SIZE,
                     "Size mismatch in initializing SIMD VectorAVX");
      a_ = _mm256_loadu_pd((double*)values.begin());
    }
    template <> inline VectorAVX<double>::VectorAVX(double value) {
      a_ = _mm256_set_pd(value, value, value, value);
    }
    template <> inline VectorAVX<double>::VectorAVX(SimdType&& a) {
      a_ = a;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::loada(const double* dat) {
      a_ = _mm256_load_pd(dat);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::load(const double* dat) {
      a_ = _mm256_loadu_pd(dat);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::partial_load(const double* dat, int n) {
      a_ = _mm256_maskload_pd(dat, avx_mask4(n));
      return *this;
    }
    template <> inline int VectorAVX<double>::size() {
      return AVX_DOUBLE_SIZE;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::storea(double* dat) {
      _mm256_store_pd(dat, a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::store(double* dat) {
      _mm256_storeu_pd(dat, a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::partial_store(double* dat, int n) {
      _mm256_maskstore_pd(dat, avx_mask4(n), a_);
      return *this;
    }
    template <> inline VectorAVX<double> VectorAVX<double>::operator-() const {
      __m256d zeros = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
      return _mm256_sub_pd(zeros, a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::operator+(const VectorAVX<double>& other) const {
      return _mm256_add_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::operator-(const VectorAVX<double>& other) const {
      return _mm256_sub_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::operator*(const VectorAVX<double>& other) const {
      return _mm256_mul_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::operator/(const VectorAVX<double>& other) const {
      return _mm256_div_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::max(const VectorAVX<double>& other) const {
      return _mm256_max_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double> VectorAVX<double>::min(const VectorAVX<double>& other) const {
      return _mm256_min_pd(a_, other.a_);
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::operator+=(const VectorAVX<double>& other) {
      a_ = _mm256_add_pd(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::operator-=(const VectorAVX<double>& other) {
      a_ = _mm256_sub_pd(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::operator*=(const VectorAVX<double>& other) {
      a_ = _mm256_mul_pd(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::operator/=(const VectorAVX<double>& other) {
      a_ = _mm256_div_pd(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<double>& VectorAVX<double>::operator=(const VectorAVX<double>& other) {
      a_ = other.a_;
      return *this;
    }

    // implementations in single
    template <> inline VectorAVX<float>::VectorAVX(std::initializer_list<float> values) {
      _cspear_assert(values.size() == AVX_SINGLE_SIZE,
                     "Size mismatch in initializing SIMD VectorAVX");
      a_ = _mm256_loadu_ps((float*)values.begin());
    }
    template <> inline VectorAVX<float>::VectorAVX(float value) {
      a_ = _mm256_set_ps(value, value, value, value, value, value, value, value);
    }
    template <> inline VectorAVX<float>::VectorAVX(SimdType&& a) {
      a_ = a;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::loada(const float* dat) {
      a_ = _mm256_load_ps(dat);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::load(const float* dat) {
      a_ = _mm256_loadu_ps(dat);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::partial_load(const float* dat, int n) {
      a_ = _mm256_maskload_ps(dat, avx_mask8(n));
      return *this;
    }
    template <> inline int VectorAVX<float>::size() {
      return AVX_SINGLE_SIZE;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::storea(float* dat) {
      _mm256_store_ps(dat, a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::store(float* dat) {
      _mm256_storeu_ps(dat, a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::partial_store(float* dat, int n) {
      _mm256_maskstore_ps(dat, avx_mask8(n), a_);
      return *this;
    }
    template <> inline VectorAVX<float> VectorAVX<float>::operator-() const {
      __m256 zeros = _mm256_set_ps(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
      return _mm256_sub_ps(zeros, a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::operator+(const VectorAVX<float>& other) const {
      return _mm256_add_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::operator-(const VectorAVX<float>& other) const {
      return _mm256_sub_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::operator*(const VectorAVX<float>& other) const {
      return _mm256_mul_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::operator/(const VectorAVX<float>& other) const {
      return _mm256_div_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::max(const VectorAVX<float>& other) const {
      return _mm256_max_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float> VectorAVX<float>::min(const VectorAVX<float>& other) const {
      return _mm256_min_ps(a_, other.a_);
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::operator+=(const VectorAVX<float>& other) {
      a_ = _mm256_add_ps(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::operator-=(const VectorAVX<float>& other) {
      a_ = _mm256_sub_ps(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::operator*=(const VectorAVX<float>& other) {
      a_ = _mm256_mul_ps(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::operator/=(const VectorAVX<float>& other) {
      a_ = _mm256_div_ps(a_, other.a_);
      return *this;
    }
    template <> inline VectorAVX<float>& VectorAVX<float>::operator=(const VectorAVX<float>& other) {
      a_ = other.a_;
      return *this;
    }
  }
}

#endif
