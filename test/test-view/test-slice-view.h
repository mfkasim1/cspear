#ifndef CSPEAR_TEST_TEST_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class SliceViewTest : public testing::Test {};

  TYPED_TEST_SUITE(SliceViewTest, RealDoubleNumber);

  TYPED_TEST(SliceViewTest,FromContiguousSlice0) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({1,csp::whole(),csp::whole()}).copy();

    std::vector<int> shape = {1,3,4};
    EXPECT_EQ(b.size(), 12);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)12, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)13, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)14, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)15, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)16, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)17, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)18, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)19, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[8], (TypeParam)20, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[9], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[10], (TypeParam)22, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[11], (TypeParam)23, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSlice1) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({csp::whole(),1,csp::whole()}).copy();

    std::vector<int> shape = {2,1,4};
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)16, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)17, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)18, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)19, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSlice2) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({csp::whole(),csp::whole(),1}).copy();

    std::vector<int> shape = {2,3,1};
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)13, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)17, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)21, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSlice3) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({0,{1,3},{2,4}}).copy();

    std::vector<int> shape = {1,2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)11, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSliceFarEnd) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({0,{1,5},{2,6}}).copy();

    std::vector<int> shape = {1,2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)11, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSliceStrided0) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({2,3,4});
    auto b = a.slice({0,{0,3,2},{1,4,2}}).copy();

    std::vector<int> shape = {1,2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)11, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(SliceViewTest,FromContiguousSliceStrided1) {
    csp::array<TypeParam> a = csp::arange<double>(24.0);
    a.reshape_({4,3,2});
    auto b = a.slice({{1,4,2},{0,3,2},1}).copy();

    std::vector<int> shape = {2,2,1};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)11, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)19, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)23, AbsTol<TypeParam>::val);
  }
}

#endif
