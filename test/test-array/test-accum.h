#ifndef CSPEAR_TEST_ARRAY_TEST_ACCUM_H
#define CSPEAR_TEST_ARRAY_TEST_ACCUM_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class AccumTestAllNumbers : public testing::Test {};
  template <typename T>
  class AccumTestSignedNumbers : public testing::Test {};
  template <typename T>
  class AccumOutlierTest : public testing::Test {};

  TYPED_TEST_SUITE(AccumTestAllNumbers, AllNumbers);
  TYPED_TEST_SUITE(AccumTestSignedNumbers, SignedNumbers);
  TYPED_TEST_SUITE(AccumOutlierTest, RealDoubleNumber);

  TYPED_TEST(AccumTestAllNumbers,CumSumAll) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    auto b = arr.cumsum();
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)13, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)20, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)29, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(AccumTestAllNumbers,CumSumAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    auto b = arr.cumsum(0);
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)13, AbsTol<TypeParam>::val);

    auto c = arr.cumsum(1);
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_EQ(c.size(), 6);
    EXPECT_NEAR(c[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)13, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)22, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(AccumTestAllNumbers,CumProdAll) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};
    auto b = arr.cumprod();
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)12, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)48, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)48, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(AccumTestAllNumbers,CumProdAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)2, (TypeParam)4, (TypeParam)1}};

    auto b = arr.cumprod(0);
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)3, AbsTol<TypeParam>::val);

    auto c = arr.cumprod(1);
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_EQ(c.size(), 6);
    EXPECT_NEAR(c[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)8, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(AccumTestSignedNumbers,CumMinAll) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};
    auto b = arr.cummin();
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(AccumTestSignedNumbers,CumMinAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)6, (TypeParam)-7, (TypeParam)-9}};

    auto b = arr.cummin(0);
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-9, AbsTol<TypeParam>::val);

    auto c = arr.cummin(1);
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_EQ(c.size(), 6);
    EXPECT_NEAR(c[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)-9, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(AccumTestSignedNumbers,CumMaxAll) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)26, (TypeParam)-7, (TypeParam)-9}};
    auto b = arr.cummax();
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)26, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)26, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)26, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(AccumTestSignedNumbers,CumMaxAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)-1, (TypeParam)21, (TypeParam)-4},
                                 {(TypeParam)-7, (TypeParam)26, (TypeParam)-9}};
    auto b = arr.cummax(0);
    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 6);
    EXPECT_NEAR(b[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)26, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-4, AbsTol<TypeParam>::val);

    auto c = arr.cummax(1);
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_EQ(c.size(), 6);
    EXPECT_NEAR(c[0], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)21, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)26, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)26, AbsTol<TypeParam>::val);
  }

  // special case
  TYPED_TEST(AccumOutlierTest,CumSumNil) {
    csp::array<TypeParam> arr = {};
    auto b = arr.cumsum();
    std::vector<int> shape = {};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 0);
  }
  TYPED_TEST(AccumOutlierTest,WrongAxis) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)4},
                                 {(TypeParam)6, (TypeParam)7, (TypeParam)9}};
    try {
      auto b = arr.cumsum(-1);
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown if index is out of bounds";
    }
    try {
      auto c = arr.cumsum(2);
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
