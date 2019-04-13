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

  // reduce
  TYPED_TEST(IndexView,ReduceAll) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    auto b = a.take({{0, 2}, {4, 5}});
    EXPECT_NEAR(b.sum(), (TypeParam)11, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(IndexView,ReduceAxis) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    auto b = a.take({{0, 2}, {4, 5}});
    auto d = b.sum(0);
    EXPECT_NEAR(d[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)8, AbsTol<TypeParam>::val);

    auto e = b.sum(1);
    EXPECT_NEAR(e[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(e[1], (TypeParam)7, AbsTol<TypeParam>::val);
  }

  // broadcast
  TYPED_TEST(IndexView,BCast0) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    auto b = a.take({{0, 2}, {4, 5}}); // (2,2): [[1,3],[2,5]]
    auto c = a.take({1,3}); // (2,): [4,7]
    auto d = b + c;
    b += c; // inplace, should change a as well

    std::vector<int> shape = {2,2};
    EXPECT_EQ(d.shape(), shape);
    EXPECT_EQ(d.size(), 4);
    EXPECT_NEAR(d[0], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[3], (TypeParam)12, AbsTol<TypeParam>::val);

    EXPECT_EQ(b.size(), 4);
    EXPECT_NEAR(b[0], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)12, AbsTol<TypeParam>::val);
    EXPECT_EQ(a.size(), 6);
    EXPECT_NEAR(a[0], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)12, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(IndexView,BCastWithFilter) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3,
                               (TypeParam)7, (TypeParam)2, (TypeParam)5};
    auto b = a.take({{0, 2}, {4, 5}}); // (2,2): [[1,3],[2,5]]
    auto c = a.filter(a <= (TypeParam)2); // (2,): [1,2]
    auto d = b + c;
    b += c; // inplace, should change a as well

    std::vector<int> shape = {2,2};
    EXPECT_EQ(d.shape(), shape);
    EXPECT_EQ(d.size(), 4);
    EXPECT_NEAR(d[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[3], (TypeParam)7, AbsTol<TypeParam>::val);

    EXPECT_EQ(b.size(), 4);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_EQ(a.size(), 6);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)7, AbsTol<TypeParam>::val);
  }
}

#endif
