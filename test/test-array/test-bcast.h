#ifndef CSPEAR_TEST_ARRAY_BCAST_H
#define CSPEAR_TEST_ARRAY_BCAST_H

#include "test_params.h"
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class BCastOp : public testing::Test {};
  template <typename T>
  class BCastOpCMP : public testing::Test {};

  TYPED_TEST_SUITE(BCastOp, RealNumbers);
  TYPED_TEST_SUITE(BCastOpCMP, RealNumbers);

  // broadcast test for the shapes
  TYPED_TEST(BCastOp,Add1) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<TypeParam> ars = {1.0};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)9.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)8.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-3.5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add2) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<TypeParam> ars = {1.0, 2.0, 4.0};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)7.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)9.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)9.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-0.5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add3) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<TypeParam> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)10.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)9.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-2.5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add4) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}};
    csp::array<TypeParam> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr + ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)4.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)5.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add5) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}, {3.1, 3.0, 2.1}};
    csp::array<TypeParam> ars = {1.0, 2.0};
    try {
      auto b = arr + ars;
      FAIL() << "A runtime error should be thrown if the dimension is mismatch.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime error should be thrown if the dimension is mismatch.";
    }
  }

  // broadcast test with the operators
  TYPED_TEST(BCastOp,Sub) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.2}};
    csp::array<TypeParam> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr - ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)1.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Mult) {
    csp::array<TypeParam> arr = {{1.0, 2.1, 3.2}};
    csp::array<TypeParam> ars = {3.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr * ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)9.6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)6.4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Div) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {4.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr / ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)0.25, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)0.75, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)1.5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOpCMP,Gt) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr > ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
  }
  TYPED_TEST(BCastOpCMP,GtEq) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr >= ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
  }
  TYPED_TEST(BCastOpCMP,Lt) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr < ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], false);
  }
  TYPED_TEST(BCastOpCMP,LtEq) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr <= ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
  }
  TYPED_TEST(BCastOpCMP,Eq) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr == ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
  }
  TYPED_TEST(BCastOpCMP,NEq) {
    csp::array<TypeParam> arr = {{1.0, 2.0, 3.0}};
    csp::array<TypeParam> ars = {1.5, 2.0};
    ars.expand_dims_(1);
    auto b = arr != ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
  }
  TEST(BCastOpBool,And) {
    csp::array<bool> arr = {{true, true, false}};
    csp::array<bool> ars = {false, true};
    ars.expand_dims_(1);
    auto b = arr && ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
  }
  TEST(BCastOpBool,Or) {
    csp::array<bool> arr = {{true, true, false}};
    csp::array<bool> ars = {false, true};
    ars.expand_dims_(1);
    auto b = arr || ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
  }
}

#endif
