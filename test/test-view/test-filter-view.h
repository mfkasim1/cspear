#ifndef CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class FilterView : public testing::Test {};

  TYPED_TEST_SUITE(FilterView, RealDoubleNumber);

  TYPED_TEST(FilterView,FromContiguous) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)3);

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)3) += (TypeParam)2;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    a.filter(a <= (TypeParam)3) += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceClip) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)3).maximum_((TypeParam)2);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto c = a.filter(a <= (TypeParam)3) + (TypeParam)2;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    auto c = a.filter(a <= (TypeParam)3) + b;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,MismatchShape) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    try {
      auto c = a.filter(b >= (TypeParam)2);
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
  }
  TYPED_TEST(FilterView,Assign) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    a.filter(a <= (TypeParam)3) = b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddAValueWithNoTrue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)0) += (TypeParam)2;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
}

#endif
