#ifndef CSPEAR_TEST_ARRAY_BCAST_H
#define CSPEAR_TEST_ARRAY_BCAST_H

#include "test_params.h"
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class BCastOp : public testing::Test {};

  TYPED_TEST_SUITE(BCastOp, AllNumbers);

  // broadcast test for the shapes
  TYPED_TEST(BCastOp,Add1) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)8, (TypeParam)7, (TypeParam)4}};
    csp::array<TypeParam> ars = {(TypeParam)1};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add2) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)8, (TypeParam)7, (TypeParam)4}};
    csp::array<TypeParam> ars = {(TypeParam)1, (TypeParam)2, (TypeParam)4};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)8, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add3) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)8, (TypeParam)7, (TypeParam)4}};
    csp::array<TypeParam> ars = {(TypeParam)1, (TypeParam)2};
    ars.expand_dims_(1);
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add4) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3}};
    csp::array<TypeParam> ars = {(TypeParam)1, (TypeParam)2};
    ars.expand_dims_(1);
    auto b = arr + ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Add5) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3},
                                 {(TypeParam)8, (TypeParam)7, (TypeParam)4}};
    csp::array<TypeParam> ars = {(TypeParam)1, (TypeParam)2};
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
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)1, (TypeParam)2};
    ars.expand_dims_(1);
    auto b = arr - ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)19, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)29, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)18, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)28, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Mult) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)3}};
    csp::array<TypeParam> ars = {(TypeParam)3, (TypeParam)2};
    ars.expand_dims_(1);
    auto b = arr * ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Div) {
    csp::array<TypeParam> arr = {{(TypeParam)40, (TypeParam)20, (TypeParam)60}};
    csp::array<TypeParam> ars = {(TypeParam)4, (TypeParam)2};
    ars.expand_dims_(1);
    auto b = arr / ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)15, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)20, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)30, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BCastOp,Gt) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
  TYPED_TEST(BCastOp,GtEq) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
  TYPED_TEST(BCastOp,Lt) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
  TYPED_TEST(BCastOp,LtEq) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
  TYPED_TEST(BCastOp,Eq) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
  TYPED_TEST(BCastOp,NEq) {
    csp::array<TypeParam> arr = {{(TypeParam)10, (TypeParam)20, (TypeParam)30}};
    csp::array<TypeParam> ars = {(TypeParam)15, (TypeParam)20};
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
