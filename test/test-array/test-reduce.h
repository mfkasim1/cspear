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

  TYPED_TEST_SUITE(ReduceTestAllNumbers, RealAndInteger);
  TYPED_TEST_SUITE(ReduceTestSignedNumbers, SignedRealAndInteger);

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
    EXPECT_NEAR(arr0[0], (TypeParam)29, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxes2) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    auto arr0 = arr.sum({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)29, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxesArray) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    csp::array<int> axes = {0,1};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)29, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxesNilAxes) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    std::vector<int> axes = {};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], (TypeParam)9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAllEmpty) {
    csp::array<TypeParam> arr = {};
    EXPECT_NEAR(arr.sum(), (TypeParam)0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxisEmpty) {
    csp::array<TypeParam> arr = {};
    auto arr0 = arr.sum(0);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);

    auto arr1 = arr.sum(1);
    std::vector<int> shape1 = {};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxes1Empty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxes2Empty) {
    csp::array<TypeParam> arr = {};
    auto arr0 = arr.sum({0,1});
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,SumAxesNilAxesEmpty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
  }

  TYPED_TEST(ReduceTestAllNumbers,ProdAll) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};
    EXPECT_NEAR(arr.prod(), (TypeParam)48, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};

    auto arr0 = arr.prod(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_NEAR(arr0[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)3, AbsTol<TypeParam>::val);

    auto arr1 = arr.prod(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_NEAR(arr1[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr1[1], (TypeParam)8, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxes1) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.prod(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)48, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxes2) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};
    auto arr0 = arr.prod({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_NEAR(arr0[0], (TypeParam)48, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxesNilAxes) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    std::vector<int> axes = {};
    auto arr0 = arr.prod(axes);
    std::vector<int> shape0 = {2,3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 6);
    EXPECT_NEAR(arr0[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[4], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr0[5], (TypeParam)9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAllEmpty) {
    csp::array<TypeParam> arr = {};
    EXPECT_NEAR(arr.prod(), (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxisEmpty) {
    csp::array<TypeParam> arr = {};
    auto arr0 = arr.prod(0);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);

    auto arr1 = arr.prod(1);
    std::vector<int> shape1 = {};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxes1Empty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.prod(axes);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxes2Empty) {
    csp::array<TypeParam> arr = {};
    auto arr0 = arr.prod({0,1});
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
  }
  TYPED_TEST(ReduceTestAllNumbers,ProdAxesNilAxesEmpty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {};
    auto arr0 = arr.prod(axes);
    std::vector<int> shape0 = {};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 0);
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
  TYPED_TEST(ReduceTestAllNumbers,MinAllEmpty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.min();
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MinAxisEmpty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.min(0);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }

    try {
      auto a = arr.min(1);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MinAxes1Empty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {0,1};
    try {
      auto a = arr.min(axes);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MinAxes2Empty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.min({0,1});
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MinAxesNilAxesEmpty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {};
    try {
      auto a = arr.min(axes);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
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
  TYPED_TEST(ReduceTestAllNumbers,MaxAllEmpty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.max();
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MaxAxisEmpty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.max(0);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }

    try {
      auto a = arr.max(1);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MaxAxes1Empty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {0,1};
    try {
      auto a = arr.max(axes);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MaxAxes2Empty) {
    csp::array<TypeParam> arr = {};
    try {
      auto a = arr.max({0,1});
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
  }
  TYPED_TEST(ReduceTestAllNumbers,MaxAxesNilAxesEmpty) {
    csp::array<TypeParam> arr = {};
    std::vector<int> axes = {};
    try {
      auto a = arr.max(axes);
      FAIL() << "A runtime_error should be thrown";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown";
    }
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
  TEST(ReduceTestBool,AllAnyAllEmpty) {
    csp::array<bool> arr = {};
    EXPECT_EQ(arr.all(), true);
    EXPECT_EQ(arr.any(), false);
  }
  TEST(ReduceTestBool,AllAnyAxisEmpty) {
    csp::array<bool> arr = {};
    auto arrall0 = arr.all(0);
    auto arrall1 = arr.all(1);
    auto arrany0 = arr.any(0);
    auto arrany1 = arr.any(1);
    std::vector<int> shape = {};

    EXPECT_EQ(arrall0.size(), 0);
    EXPECT_EQ(arrall1.size(), 0);
    EXPECT_EQ(arrany0.size(), 0);
    EXPECT_EQ(arrany1.size(), 0);

    EXPECT_EQ(arrall0.shape(), shape);
    EXPECT_EQ(arrall1.shape(), shape);
    EXPECT_EQ(arrany0.shape(), shape);
    EXPECT_EQ(arrany1.shape(), shape);
  }
  TEST(ReduceTestBool,AllAnyAxes1Empty) {
    csp::array<bool> arr = {};
    auto a1 = arr.all({0,1});
    auto a2 = arr.any({0,1});
    std::vector<int> shape = {};
    EXPECT_EQ(a1.size(), 0);
    EXPECT_EQ(a2.size(), 0);
    EXPECT_EQ(a1.shape(), shape);
    EXPECT_EQ(a2.shape(), shape);
  }
  TEST(ReduceTestBool,AllAnyNilAxesEmpty) {
    csp::array<bool> arr = {};
    std::vector<int> axes = {};
    auto a1 = arr.all(axes);
    auto a2 = arr.any(axes);
    std::vector<int> shape = {};

    EXPECT_EQ(a1.size(), 0);
    EXPECT_EQ(a2.size(), 0);
    EXPECT_EQ(a1.shape(), shape);
    EXPECT_EQ(a2.shape(), shape);
  }

  TEST(ReduceOutlierTest,WrongAxis) {
    csp::array<double> arr = {{1.0, 2.0, 4.0},
                              {6.0, 7.0, 9.0}};
    try {
      auto b = arr.sum(-1);
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
    try {
      auto c = arr.sum(2);
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
  }
}

#endif
