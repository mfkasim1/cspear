#ifndef CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  template <typename T>
  class FilterView : public testing::Test {};

  using testing::Types;
  typedef Types<double, float> RealNumbers;
  TYPED_TEST_SUITE(FilterView, RealNumbers);

  TYPED_TEST(FilterView,FromContiguous) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto b = a.filter(a < 3.1);

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 2.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddAValue) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a.filter(a < 3.1) += 2.0;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], 5.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], 6.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], 4.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], 5.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddArray) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<TypeParam> b = {2.0, 6.0, 4.2};
    a.filter(a < 3.1) += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], 9.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], 6.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], 6.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], 5.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceClip) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a.filter(a < 3.1).clip_lb_(2.5);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 2.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], 6.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], 2.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], 5.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddAValue) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto c = a.filter(a < 3.1) + 2.0;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], 5.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], 4.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddArray) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<TypeParam> b = {2.0, 6.0, 4.2};
    auto c = a.filter(a < 3.1) + b;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], 9.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], 6.3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,MismatchShape) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<TypeParam> b = {2.0, 6.0, 4.2};
    try {
      auto c = a.filter(b > 2.1);
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
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<TypeParam> b = {2.0, 6.0, 4.2};
    a.filter(a < 3.1) = b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], 6.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], 5.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddAValueWithNoTrue) {
    csp::array<TypeParam> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a.filter(a < -3.1) += 2.0;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], 4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], 6.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], 2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], 5.2, AbsTol<TypeParam>::val);
  }
}

#endif
