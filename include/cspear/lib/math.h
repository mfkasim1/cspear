#ifndef CSPEAR_LIB_MATH_H
#define CSPEAR_LIB_MATH_H

#include <cmath>
#include <cspear/core/array.h>
#include <cspear/core/array-math.h>
#include <cspear/lib/init.h>

namespace csp {
  // works on array

  template <typename T, typename I>
  array<T,I> sin(const array<T,I>& a) {
    return a.sin();
  }

  template <typename T, typename I>
  array<T,I>& sin_(array<T,I>& a) {
    return a.sin_();
  }

  template <typename T, typename I>
  array<T,I> cos(const array<T,I>& a) {
    return a.cos();
  }

  template <typename T, typename I>
  array<T,I>& cos_(array<T,I>& a) {
    return a.cos_();
  }

  template <typename T, typename I>
  array<T,I> tan(const array<T,I>& a) {
    return a.tan();
  }

  template <typename T, typename I>
  array<T,I>& tan_(array<T,I>& a) {
    return a.tan_();
  }

  template <typename T, typename I>
  array<T,I> asin(const array<T,I>& a) {
    return a.asin();
  }

  template <typename T, typename I>
  array<T,I>& asin_(array<T,I>& a) {
    return a.asin_();
  }

  template <typename T, typename I>
  array<T,I> acos(const array<T,I>& a) {
    return a.acos();
  }

  template <typename T, typename I>
  array<T,I>& acos_(array<T,I>& a) {
    return a.acos_();
  }

  template <typename T, typename I>
  array<T,I> atan(const array<T,I>& a) {
    return a.atan();
  }

  template <typename T, typename I>
  array<T,I>& atan_(array<T,I>& a) {
    return a.atan_();
  }

  template <typename T, typename I>
  array<T,I> atan2(const array<T,I>& a) {
    return a.atan2();
  }

  template <typename T, typename I>
  array<T,I>& atan2_(array<T,I>& a) {
    return a.atan2_();
  }

  template <typename T, typename I>
  array<T,I> sinh(const array<T,I>& a) {
    return a.sinh();
  }

  template <typename T, typename I>
  array<T,I>& sinh_(array<T,I>& a) {
    return a.sinh_();
  }

  template <typename T, typename I>
  array<T,I> cosh(const array<T,I>& a) {
    return a.cosh();
  }

  template <typename T, typename I>
  array<T,I>& cosh_(array<T,I>& a) {
    return a.cosh_();
  }

  template <typename T, typename I>
  array<T,I> tanh(const array<T,I>& a) {
    return a.tanh();
  }

  template <typename T, typename I>
  array<T,I>& tanh_(array<T,I>& a) {
    return a.tanh_();
  }

  template <typename T, typename I>
  array<T,I> asinh(const array<T,I>& a) {
    return a.asinh();
  }

  template <typename T, typename I>
  array<T,I>& asinh_(array<T,I>& a) {
    return a.asinh_();
  }

  template <typename T, typename I>
  array<T,I> acosh(const array<T,I>& a) {
    return a.acosh();
  }

  template <typename T, typename I>
  array<T,I>& acosh_(array<T,I>& a) {
    return a.acosh_();
  }

  template <typename T, typename I>
  array<T,I> atanh(const array<T,I>& a) {
    return a.atanh();
  }

  template <typename T, typename I>
  array<T,I>& atanh_(array<T,I>& a) {
    return a.atanh_();
  }

  template <typename T, typename I>
  array<T,I> exp(const array<T,I>& a) {
    return a.exp();
  }

  template <typename T, typename I>
  array<T,I>& exp_(array<T,I>& a) {
    return a.exp_();
  }

  template <typename T, typename I>
  array<T,I> log(const array<T,I>& a) {
    return a.log();
  }

  template <typename T, typename I>
  array<T,I>& log_(array<T,I>& a) {
    return a.log_();
  }

  template <typename T, typename I>
  array<T,I> log10(const array<T,I>& a) {
    return a.log10();
  }

  template <typename T, typename I>
  array<T,I>& log10_(array<T,I>& a) {
    return a.log10_();
  }

  template <typename T, typename I>
  array<T,I> exp2(const array<T,I>& a) {
    return a.exp2();
  }

  template <typename T, typename I>
  array<T,I>& exp2_(array<T,I>& a) {
    return a.exp2_();
  }

  template <typename T, typename I>
  array<T,I> expm1(const array<T,I>& a) {
    return a.expm1();
  }

  template <typename T, typename I>
  array<T,I>& expm1_(array<T,I>& a) {
    return a.expm1_();
  }

  template <typename T, typename I>
  array<T,I> log1p(const array<T,I>& a) {
    return a.log1p();
  }

  template <typename T, typename I>
  array<T,I>& log1p_(array<T,I>& a) {
    return a.log1p_();
  }

  template <typename T, typename I>
  array<T,I> log2(const array<T,I>& a) {
    return a.log2();
  }

  template <typename T, typename I>
  array<T,I>& log2_(array<T,I>& a) {
    return a.log2_();
  }

  template <typename T, typename I>
  array<T,I> sqrt(const array<T,I>& a) {
    return a.sqrt();
  }

  template <typename T, typename I>
  array<T,I>& sqrt_(array<T,I>& a) {
    return a.sqrt_();
  }

  template <typename T, typename I>
  array<T,I> cbrt(const array<T,I>& a) {
    return a.cbrt();
  }

  template <typename T, typename I>
  array<T,I>& cbrt_(array<T,I>& a) {
    return a.cbrt_();
  }

  template <typename T, typename I>
  array<T,I> sqr(const array<T,I>& a) {
    return a.sqr();
  }

  template <typename T, typename I>
  array<T,I>& sqr_(array<T,I>& a) {
    return a.sqr_();
  }

  template <typename T, typename I>
  array<T,I> cube(const array<T,I>& a) {
    return a.cube();
  }

  template <typename T, typename I>
  array<T,I>& cube_(array<T,I>& a) {
    return a.cube_();
  }

  template <typename T, typename I>
  array<T,I> erf(const array<T,I>& a) {
    return a.erf();
  }

  template <typename T, typename I>
  array<T,I>& erf_(array<T,I>& a) {
    return a.erf_();
  }

  template <typename T, typename I>
  array<T,I> erfc(const array<T,I>& a) {
    return a.erfc();
  }

  template <typename T, typename I>
  array<T,I>& erfc_(array<T,I>& a) {
    return a.erfc_();
  }

  template <typename T, typename I>
  array<T,I> tgamma(const array<T,I>& a) {
    return a.tgamma();
  }

  template <typename T, typename I>
  array<T,I>& tgamma_(array<T,I>& a) {
    return a.tgamma_();
  }

  template <typename T, typename I>
  array<T,I> lgamma(const array<T,I>& a) {
    return a.lgamma();
  }

  template <typename T, typename I>
  array<T,I>& lgamma_(array<T,I>& a) {
    return a.lgamma_();
  }

  template <typename T, typename I>
  array<T,I> ceil(const array<T,I>& a) {
    return a.ceil();
  }

  template <typename T, typename I>
  array<T,I>& ceil_(array<T,I>& a) {
    return a.ceil_();
  }

  template <typename T, typename I>
  array<T,I> floor(const array<T,I>& a) {
    return a.floor();
  }

  template <typename T, typename I>
  array<T,I>& floor_(array<T,I>& a) {
    return a.floor_();
  }

  template <typename T, typename I>
  array<T,I> round(const array<T,I>& a) {
    return a.round();
  }

  template <typename T, typename I>
  array<T,I>& round_(array<T,I>& a) {
    return a.round_();
  }

  template <typename T, typename I>
  array<T,I> fabs(const array<T,I>& a) {
    return a.fabs();
  }

  template <typename T, typename I>
  array<T,I>& fabs_(array<T,I>& a) {
    return a.fabs_();
  }

  // works on a single number

  template <typename T>
  inline T sin(T a) {
    return std::sin(a);
  }

  template <typename T>
  inline T cos(T a) {
    return std::cos(a);
  }

  template <typename T>
  inline T tan(T a) {
    return std::tan(a);
  }

  template <typename T>
  inline T asin(T a) {
    return std::asin(a);
  }

  template <typename T>
  inline T acos(T a) {
    return std::acos(a);
  }

  template <typename T>
  inline T atan(T a) {
    return std::atan(a);
  }

  template <typename T>
  inline T atan2(T a) {
    return std::atan2(a);
  }

  template <typename T>
  inline T sinh(T a) {
    return std::sinh(a);
  }

  template <typename T>
  inline T cosh(T a) {
    return std::cosh(a);
  }

  template <typename T>
  inline T tanh(T a) {
    return std::tanh(a);
  }

  template <typename T>
  inline T asinh(T a) {
    return std::asinh(a);
  }

  template <typename T>
  inline T acosh(T a) {
    return std::acosh(a);
  }

  template <typename T>
  inline T atanh(T a) {
    return std::atanh(a);
  }

  template <typename T>
  inline T exp(T a) {
    return std::exp(a);
  }

  template <typename T>
  inline T log(T a) {
    return std::log(a);
  }

  template <typename T>
  inline T log10(T a) {
    return std::log10(a);
  }

  template <typename T>
  inline T exp2(T a) {
    return std::exp2(a);
  }

  template <typename T>
  inline T expm1(T a) {
    return std::expm1(a);
  }

  template <typename T>
  inline T log1p(T a) {
    return std::log1p(a);
  }

  template <typename T>
  inline T log2(T a) {
    return std::log2(a);
  }

  template <typename T>
  inline T sqrt(T a) {
    return std::sqrt(a);
  }

  template <typename T>
  inline T cbrt(T a) {
    return std::cbrt(a);
  }

  template <typename T>
  inline T erf(T a) {
    return std::erf(a);
  }

  template <typename T>
  inline T erfc(T a) {
    return std::erfc(a);
  }

  template <typename T>
  inline T tgamma(T a) {
    return std::tgamma(a);
  }

  template <typename T>
  inline T lgamma(T a) {
    return std::lgamma(a);
  }

  template <typename T>
  inline T ceil(T a) {
    return std::ceil(a);
  }

  template <typename T>
  inline T floor(T a) {
    return std::floor(a);
  }

  template <typename T>
  inline T round(T a) {
    return std::round(a);
  }

  template <typename T>
  inline T fabs(T a) {
    return std::fabs(a);
  }

  template <typename T>
  inline T sqr(T a) {
    return a*a;
  }

  template <typename T>
  inline T cube(T a) {
    return a*a*a;
  }

}

#endif
