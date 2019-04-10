#ifndef CSPEAR_TEST_TEST_LIB_TEST_MATH_H
#define CSPEAR_TEST_TEST_LIB_TEST_MATH_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  TEST(MathExposeTest,NonInplace) {
    csp::array<double> a = {0.2, 0.5, 1.0};
    auto c = csp::cos(a);

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], 0.9800665778412416, AbsTol<double>::val);
    EXPECT_NEAR(c[1], 0.8775825618903728, AbsTol<double>::val);
    EXPECT_NEAR(c[2], 0.5403023058681398, AbsTol<double>::val);
    EXPECT_EQ(a.size(), 3);
    EXPECT_NEAR(a[0], 0.2, AbsTol<double>::val);
    EXPECT_NEAR(a[1], 0.5, AbsTol<double>::val);
    EXPECT_NEAR(a[2], 1.0, AbsTol<double>::val);
  }
  TEST(MathExposeTest,Inplace) {
    csp::array<double> a = {0.2, 0.5, 1.0};
    csp::cos_(a);

    std::vector<int> shape = {3};
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 0.9800665778412416, AbsTol<double>::val);
    EXPECT_NEAR(a[1], 0.8775825618903728, AbsTol<double>::val);
    EXPECT_NEAR(a[2], 0.5403023058681398, AbsTol<double>::val);
  }
  TEST(MathExposeTest,Standalone) {
    EXPECT_NEAR(csp::cos(0.2), 0.9800665778412416, AbsTol<double>::val);
  }
  TEST(MathExposeTest,FcnDoesExist) {
    csp::array<double> a = {0.2, 0.5, 1.0};
    csp::array<double> b = {0.8, 0.3, 0.9};

    auto c = csp::cos(a);
    auto d = csp::sin(a);
    auto e = csp::tan(a);
    auto f = csp::acos(a);
    auto g = csp::asin(a);
    auto h = csp::atan(a);
    auto i = csp::atan2(a,b);
    auto j = csp::cosh(a);
    auto k = csp::sinh(a);
    auto l = csp::tanh(a);
    auto m = csp::acosh(a);
    auto n = csp::asinh(a);
    auto o = csp::atanh(a);
    auto p = csp::exp(a);
    auto r = csp::log(a);
    auto s = csp::log10(a);
    auto t = csp::exp2(a);
    auto u = csp::expm1(a);
    auto v = csp::log1p(a);
    auto w = csp::log2(a);
    auto x = csp::pow(a,b);
    auto y = csp::sqrt(a);
    auto z = csp::cbrt(a);
    auto aa = csp::hypot(a,b);
    auto ab = csp::erf(a);
    auto ac = csp::erfc(a);
    auto ad = csp::tgamma(a);
    auto ae = csp::lgamma(a);
    auto af = csp::ceil(a);
    auto ag = csp::trunc(a);
    auto ah = csp::floor(a);
    auto ai = csp::round(a);
    auto aj = csp::abs(a);
  }
}

#endif
