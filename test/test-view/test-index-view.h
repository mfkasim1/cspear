#ifndef CSPEAR_TEST_TEST_VIEW_TEST_INDEX_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_INDEX_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class IndexView : public testing::Test {};
  template <typename T>
  class IndexViewOutlierTest : public testing::Test {};

  TYPED_TEST_SUITE(IndexView, RealDoubleNumber);
  TYPED_TEST_SUITE(IndexViewOutlierTest, RealDoubleNumber);

  TYPED_TEST(IndexView,From1DBracket) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    auto b = a.take({0, 2, 4, 5});

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(IndexView,From2DBracket) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.take({0, 2, 4, 5});

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(IndexView,From1DArray) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    csp::array<int> c = {0, 2, 4, 5};
    auto b = a.take(c);

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(IndexView,From1DArray2D) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    csp::array<int> c = {{0, 2}, {4, 5}};
    auto b = a.take(c);

    std::vector<int> shape = {2, 2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)5, AbsTol<TypeParam>::val);
  }
}

#endif
