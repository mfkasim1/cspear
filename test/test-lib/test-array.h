#ifndef CSPEAR_TEST_TEST_LIB_TEST_ARRAY_H
#define CSPEAR_TEST_TEST_LIB_TEST_ARRAY_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class ArrayFcnExposeTest : public testing::Test {};

  using testing::Types;
  TYPED_TEST_SUITE(ArrayFcnExposeTest, RealDoubleNumber);

  TYPED_TEST(ArrayFcnExposeTest,NonInplace) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3};
    csp::array<TypeParam> b = {(TypeParam)3, (TypeParam)2, (TypeParam)2};
    auto c = csp::add(a, b);

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ArrayFcnExposeTest,Inplace) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3};
    csp::array<TypeParam> b = {(TypeParam)3, (TypeParam)2, (TypeParam)2};
    csp::add_(a, b);

    std::vector<int> shape = {3};
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ArrayFcnExposeTest,FcnDoesExist) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3};
    csp::array<TypeParam> b = {(TypeParam)3, (TypeParam)2, (TypeParam)2};

    // arithmetic
    auto c = csp::add(a, b);
    csp::add_(a, b);
    auto d = csp::sub(a, b);
    csp::sub_(a, b);
    auto e = csp::mult(a, b);
    csp::mult_(a, b);
    auto f = csp::div(a, b);
    csp::div_(a, b);
    auto g = csp::reciprocal(a, (TypeParam)1);
    auto h = csp::neg(a);
    csp::neg_(a);

    // reduce
    auto i = csp::sum(a);
    auto j = csp::sum(a, 0);
    auto k = csp::prod(a);
    auto l = csp::max(a);
    auto m = csp::min(a);
    auto n = csp::all(a);
    auto o = csp::any(a);

    // accumulate
    auto p = csp::cumsum(a);
    csp::cumsum_(a);
    auto r = csp::cumprod(a);
    auto s = csp::cummax(a);
    auto t = csp::cummin(a);

    // comparison
    auto u = csp::gt(a, b);
    auto v = csp::lt(a, b);
    auto w = csp::gteq(a, b);
    auto x = csp::lteq(a, b);
    auto y = csp::eq(a, b);
    auto z = csp::neq(a, b);

    // clip
    auto aa = csp::clip(a, b, (TypeParam)1);
    auto ab = csp::maximum(a, b);
    auto ac = csp::minimum(a, b);

    // fill / assignment
    auto ad = csp::fill(a, b);
    csp::fill_(a, b);
  }
  TEST(ArrayFcnExposeBoolTest,BoolFcnDoesExist) {
    csp::array<bool> a = {false, true, false};
    csp::array<bool> b = {false, true, true};

    auto c = csp::logical_not(a);
    auto d = csp::logical_and(a, b);
    auto e = csp::logical_or(a, b);
  }
}

#endif
