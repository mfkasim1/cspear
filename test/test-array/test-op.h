#ifndef CSPEAR_TEST_ARRAY_TEST_OP_H
#define CSPEAR_TEST_ARRAY_TEST_OP_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class UnaryOp : public testing::Test {};
  template <typename T>
  class BinaryOpWithAValue : public testing::Test {};
  template <typename T>
  class BinaryOpWithAValueCmp : public testing::Test {};
  template <typename T>
  class InplaceBinaryOpWithAValue : public testing::Test {};
  template <typename T>
  class BinaryOp : public testing::Test {};
  template <typename T>
  class InplaceBinaryOp : public testing::Test {};

  TYPED_TEST_SUITE(UnaryOp, RealNumbers);
  TYPED_TEST_SUITE(BinaryOpWithAValue, RealNumbers);
  TYPED_TEST_SUITE(BinaryOpWithAValueCmp, RealNumbers);
  TYPED_TEST_SUITE(InplaceBinaryOpWithAValue, RealNumbers);
  TYPED_TEST_SUITE(BinaryOp, RealNumbers);
  TYPED_TEST_SUITE(InplaceBinaryOp, RealNumbers);

  TYPED_TEST(UnaryOp,Indexing) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    EXPECT_NEAR(arr.at({0,1}), 4.1, AbsTol<TypeParam>::val);
    csp::array<TypeParam> arr2 = {3.0, 4.1, -5.0, 0.0};
    EXPECT_NEAR(arr2.at({0,}), 3.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(UnaryOp,Neg) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = -arr;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], -3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], -4.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 5.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], -0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], -0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], 4.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], -2.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Add) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr + 3.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 7.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 3.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 3.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 5.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Sub) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr - 3.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -8.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], -3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], -2.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], -2.8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -7.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], -0.9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Mult) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr * 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 4.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Div) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr / 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 1.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -2.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.05, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Rdiv) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.reciprocal(2.0); // 2.0 / arr
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 20.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,ClipLb) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip_lb(2.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,ClipUb) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip_ub(2.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -5.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Clip) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip(-1.0, 3.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(BinaryOpWithAValueCmp,Gt) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr > 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], false, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValueCmp,GtEq) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr >= 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], true, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValueCmp,Lt) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr < -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], false, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValueCmp,LtEq) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr <= -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], false, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValueCmp,Eq) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr == -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], false, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValueCmp,NEq) {
    csp::array<TypeParam> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr != -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], true, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], false, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], true, AbsTol<TypeParam>::val);
  }
  TEST(BinaryOpWithAValueBool,Not) {
    csp::array<bool> arr = {true, false, false};
    auto b = !arr;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
  }
  TEST(BinaryOpWithAValueBool,And) {
    csp::array<bool> arr = {{true, false, true}, {false, false, true}};
    auto b = arr && true;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
    auto c = arr && false;
    EXPECT_EQ(c.shape(), arr.shape());
    EXPECT_EQ(c.size(), arr.size());
    EXPECT_EQ(c[0], false);
    EXPECT_EQ(c[1], false);
    EXPECT_EQ(c[2], false);
    EXPECT_EQ(c[3], false);
    EXPECT_EQ(c[4], false);
    EXPECT_EQ(c[5], false);
  }
  TEST(BinaryOpWithAValueBool,Or) {
    csp::array<bool> arr = {{true, false, true}, {false, false, true}};
    auto b = arr || false;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
    auto c = arr || true;
    EXPECT_EQ(c.shape(), arr.shape());
    EXPECT_EQ(c.size(), arr.size());
    EXPECT_EQ(c[0], true);
    EXPECT_EQ(c[1], true);
    EXPECT_EQ(c[2], true);
    EXPECT_EQ(c[3], true);
    EXPECT_EQ(c[4], true);
    EXPECT_EQ(c[5], true);
  }

  TYPED_TEST(InplaceBinaryOpWithAValue,Add) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    arr += 3.0;
    EXPECT_NEAR(arr[0], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], 7.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], -2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], 3.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], 3.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[6], -1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[7], 5.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Sub) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b -= 3.0;
    EXPECT_NEAR(b[0], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -8.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], -3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], -2.9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], -2.8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -7.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], -0.9, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Mult) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b *= 2.0;
    EXPECT_NEAR(b[0], 6.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 4.2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Div) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b /= 2.0;
    EXPECT_NEAR(b[0], 1.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -2.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.05, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Rdiv) {
    csp::array<TypeParam> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.reciprocal_(2.0);
    EXPECT_NEAR(b[0], 1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 20.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -0.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,ClipLb) {
    csp::array<TypeParam> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_lb_(2.0);
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,ClipUb) {
    csp::array<TypeParam> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_ub_(2.0);
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -5.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Clip) {
    csp::array<TypeParam> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_(-1.0, 3.0);
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.0, AbsTol<TypeParam>::val);
  }

  // binary op with another array
  TYPED_TEST(BinaryOp,Add) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr + ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 6.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 2.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 3.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Sub) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr - ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], -1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], -1.8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -6.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Mult) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr * ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -25.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Div) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr / ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Aliasing) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b = b + ars;
    EXPECT_EQ(b.shape(), ars.shape());
    EXPECT_EQ(b.size(), ars.size());
    EXPECT_NEAR(b[0], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 6.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 2.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 3.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Gt) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr > ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], false);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], true);
  }
  TYPED_TEST(BinaryOp,GtEq) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr >= ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], false);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], true);
  }
  TYPED_TEST(BinaryOp,Lt) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr < ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], true);
    EXPECT_EQ(b[7], false);
  }
  TYPED_TEST(BinaryOp,LtEq) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr <= ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], true);
    EXPECT_EQ(b[7], false);
  }
  TYPED_TEST(BinaryOp,Eq) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 0.0}, {0.1, 2.0, 2.0, 1.0}};
    auto b = arr == ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], false);
  }
  TYPED_TEST(BinaryOp,NEq) {
    csp::array<TypeParam> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, -5.0, 0.0}, {0.1, 2.0, 2.0, 1.0}};
    auto b = arr != ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], true);
    EXPECT_EQ(b[7], true);
  }
  TEST(BinaryOpBool,And) {
    csp::array<bool> arr = {{true, true, false, false}, {true, true, false, false}};
    csp::array<bool> ars = {{true, false, false, false}, {true, true, false, true}};
    auto b = arr && ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], false);
  }
  TEST(BinaryOpBool,Or) {
    csp::array<bool> arr = {{true, true, false, false}, {true, true, false, false}};
    csp::array<bool> ars = {{true, false, false, false}, {true, true, false, true}};
    auto b = arr || ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], true);
  }

  // inplace binary operator with another array
  TYPED_TEST(InplaceBinaryOp,Fill) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b.fill_(0.0);
    EXPECT_NEAR(b[0], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 0.0, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Add) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b += ars;
    EXPECT_NEAR(b[0], 4.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 6.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 2.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 3.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Sub) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b -= ars;
    EXPECT_NEAR(b[0], 2.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -10.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], -1.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], -1.8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -6.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 1.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Mult) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b *= ars;
    EXPECT_NEAR(b[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -25.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Div) {
    csp::array<TypeParam> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<TypeParam> ars = {{1.0, 2.0, 5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    b /= ars;
    EXPECT_NEAR(b[0], 3.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -1.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 0.0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 0.1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -2.05, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 2.1, AbsTol<TypeParam>::val);
  }
}
#endif
