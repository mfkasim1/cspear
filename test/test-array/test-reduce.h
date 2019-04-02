#ifndef CSPEAR_TEST_ARRAY_TEST_REDUCE_H
#define CSPEAR_TEST_ARRAY_TEST_REDUCE_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class ReduceTest : public testing::Test {};

  using testing::Types;
  typedef Types<double, float> RealNumbers;
  TYPED_TEST_SUITE(ReduceTest, RealNumbers);

  TYPED_TEST(ReduceTest,SumAll) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    EXPECT_NEAR(arr.sum(), 29.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,SumAxis) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};

    auto arr0 = arr.sum(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], 7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], 9.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], 13.0, AbsTol<TypeParam>::val);

    auto arr1 = arr.sum(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], 7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], 22.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,SumAxes1) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 29.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,SumAxes2) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    auto arr0 = arr.sum({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 29.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,SumAxesNilAxes) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    std::vector<int> axes = {};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], 7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], 9.0, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(ReduceTest,MinAll) {
    csp::array<TypeParam> arr = {{10.0, 2.0, 14.0}, {6.0, 7.0, 9.0}};
    EXPECT_NEAR(arr.min(), 2.0, AbsTol<TypeParam>::val);

    csp::array<TypeParam> arr1 = {{-10.0, 2.0, 14.0}, {-6.0, -7.0, 9.0}};
    EXPECT_NEAR(arr1.min(), -10.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MinAxis) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};

    auto arr0 = arr.min(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], -7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], -9.0, AbsTol<TypeParam>::val);

    auto arr1 = arr.min(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], -4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], -9.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MinAxes1) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.min(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], -9.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MinAxes2) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    auto arr0 = arr.min({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], -9.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MinAxesNilAxes) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    std::vector<int> axes = {};
    auto arr0 = arr.min(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], 7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], 9.0, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(ReduceTest,MaxAll) {
    csp::array<TypeParam> arr = {{10.0, 2.0, 14.0}, {6.0, 7.0, 9.0}};
    EXPECT_NEAR(arr.max(), 14.0, AbsTol<TypeParam>::val);

    csp::array<TypeParam> arr1 = {{-10.0, -2.0, -14.0}, {-6.0, -7.0, -9.0}};
    EXPECT_NEAR(arr1.max(), -2.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MaxAxis) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};

    auto arr0 = arr.max(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], 21.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], -4.0, AbsTol<TypeParam>::val);

    auto arr1 = arr.max(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], 21.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], 6.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MaxAxes1) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.max(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 21.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MaxAxes2) {
    csp::array<TypeParam> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    auto arr0 = arr.max({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 21.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTest,MaxAxesNilAxes) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    std::vector<int> axes = {};
    auto arr0 = arr.max(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], 7.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], 9.0, AbsTol<TypeParam>::val);
  }

  TEST(ReduceTestBool,AllAnyAll) {
    csp::array<bool> arr = {{false, true, true}, {true, true, true}};
    EXPECT_EQ(arr.all(), false);
    EXPECT_EQ(arr.any(), true);
  }
  TEST(ReduceTestBool,AllAnyAxis) {
    csp::array<bool> arr = {{false, true, true}, {true, true, true}};
    auto arrall0 = arr.all(0);
    auto arrall1 = arr.all(1);
    auto arrany0 = arr.any(0);
    auto arrany1 = arr.any(1);

    EXPECT_EQ(arrall0.size(), 3);
    EXPECT_EQ(arrall1.size(), 2);
    EXPECT_EQ(arrany0.size(), 3);
    EXPECT_EQ(arrany1.size(), 2);

    EXPECT_EQ(arrall0[0], false);
    EXPECT_EQ(arrall0[1], true);
    EXPECT_EQ(arrall0[2], true);
    EXPECT_EQ(arrall1[0], false);
    EXPECT_EQ(arrall1[1], true);

    EXPECT_EQ(arrany0[0], true);
    EXPECT_EQ(arrany0[1], true);
    EXPECT_EQ(arrany0[2], true);
    EXPECT_EQ(arrany1[0], true);
    EXPECT_EQ(arrany1[1], true);
  }

  TEST(ReduceTestBool,AllAnyAxes1) {
    csp::array<bool> arr = {{false, true, true}, {true, true, true}};
    auto a1 = arr.all({0,1});
    auto a2 = arr.any({0,1});
    EXPECT_EQ(a1.size(), 1);
    EXPECT_EQ(a2.size(), 1);
    EXPECT_EQ(a1[0], false);
    EXPECT_EQ(a2[0], true);
  }
  TEST(ReduceTestBool,AllAnyNilAxes) {
    csp::array<bool> arr = {{false, true, true}, {true, true, true}};
    std::vector<int> axes = {};
    auto a1 = arr.all(axes);
    auto a2 = arr.any(axes);
    std::vector<int> shape = {2,3};

    EXPECT_EQ(a1.size(), 6);
    EXPECT_EQ(a2.size(), 6);
    EXPECT_EQ(a1.shape(), shape);
    EXPECT_EQ(a2.shape(), shape);
    EXPECT_EQ(a1[0], false);
    EXPECT_EQ(a1[1], true);
    EXPECT_EQ(a1[2], true);
    EXPECT_EQ(a1[3], true);
    EXPECT_EQ(a1[4], true);
    EXPECT_EQ(a1[5], true);

    EXPECT_EQ(a2[0], false);
    EXPECT_EQ(a2[1], true);
    EXPECT_EQ(a2[2], true);
    EXPECT_EQ(a2[3], true);
    EXPECT_EQ(a2[4], true);
    EXPECT_EQ(a2[5], true);
  }
}

#endif
