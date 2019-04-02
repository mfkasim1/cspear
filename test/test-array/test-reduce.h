#ifndef CSPEAR_TEST_ARRAY_TEST_REDUCE_H
#define CSPEAR_TEST_ARRAY_TEST_REDUCE_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class ReduceTestAllNumbers : public testing::Test {};
  template <typename T>
  class ReduceTestSignedNumbers : public testing::Test {};

  TYPED_TEST_SUITE(ReduceTestAllNumbers, AllNumbers);
  TYPED_TEST_SUITE(ReduceTestSignedNumbers, SignedNumbers);

  TYPED_TEST(ReduceTestAllNumbers,SumAll) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    EXPECT_NEAR(arr.sum(), (TypeParam)29, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};

    auto arr0 = arr.sum(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)13, AbsTol<TypeParam>::val);

    auto arr1 = arr.sum(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], (TypeParam)22, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxes1) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 29.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxes2) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    auto arr0 = arr.sum({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], 29.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxesNilAxes) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
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

  TYPED_TEST(ReduceTestSignedNumbers,MinAll) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)2, (TypeParam)14},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    EXPECT_NEAR(arr.min(), (TypeParam)2, AbsTol<TypeParam>::val);

    csp::array<TypeParam> arr1 = {{(TypeParam)-10, (TypeParam)2, (TypeParam)14},
                                 {(TypeParam)-6, (TypeParam)-7, (TypeParam)9}};
    EXPECT_NEAR(arr1.min(), (TypeParam)-10, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MinAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};

    auto arr0 = arr.min(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)-9, AbsTol<TypeParam>::val);

    auto arr1 = arr.min(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], (TypeParam)-9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MinAxes1) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.min(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)-9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MinAxes2) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    auto arr0 = arr.min({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)-9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MinAxesNilAxes) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    std::vector<int> axes = {};
    auto arr0 = arr.min(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], (TypeParam)-9, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(ReduceTestSignedNumbers,MaxAll) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)2, (TypeParam)14},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    EXPECT_NEAR(arr.max(), (TypeParam)14, AbsTol<TypeParam>::val);

    csp::array<TypeParam> arr1 = {{(TypeParam)-10, (TypeParam)2, (TypeParam)14},
                                 {(TypeParam)-6, (TypeParam)-7, (TypeParam)9}};
    EXPECT_NEAR(arr1.max(), (TypeParam)14, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MaxAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};

    auto arr0 = arr.max(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)-4, AbsTol<TypeParam>::val);

    auto arr1 = arr.max(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MaxAxes1) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.max(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)21, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MaxAxes2) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    auto arr0 = arr.max({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)21, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestSignedNumbers,MaxAxesNilAxes) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    std::vector<int> axes = {};
    auto arr0 = arr.max(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], (TypeParam)-9, AbsTol<TypeParam>::val);
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
