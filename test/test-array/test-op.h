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
  template <typename T>
  class TernaryOpWithValues : public testing::Test {};
  template <typename T>
  class InplaceTernaryOpWithValues : public testing::Test {};

  TYPED_TEST_SUITE(UnaryOp,                   SignedNumbers);
  TYPED_TEST_SUITE(BinaryOpWithAValue,        SignedNumbers);
  TYPED_TEST_SUITE(BinaryOpWithAValueCmp,     SignedNumbers);
  TYPED_TEST_SUITE(InplaceBinaryOpWithAValue, SignedNumbers);
  TYPED_TEST_SUITE(BinaryOp,                  SignedNumbers);
  TYPED_TEST_SUITE(InplaceBinaryOp,           SignedNumbers);
  TYPED_TEST_SUITE(TernaryOpWithValues,       SignedNumbers);
  TYPED_TEST_SUITE(InplaceTernaryOpWithValues,SignedNumbers);

  TYPED_TEST(UnaryOp,Indexing) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    EXPECT_NEAR(arr.at({0,1}), (TypeParam)4, AbsTol<TypeParam>::val);
    csp::array<TypeParam> arr2 = {(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0};
    EXPECT_NEAR(arr2.at({0,}), (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(UnaryOp,Neg) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = -arr;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)-2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Add) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr + (TypeParam)3;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], 6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], 7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], -2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], 3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], 3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], 3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], -1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], 5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Sub) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr - (TypeParam)3;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)-1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Mult) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr * (TypeParam)2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Div) {
    csp::array<TypeParam> arr = {{(TypeParam)6, (TypeParam)4, (TypeParam)-8, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr / (TypeParam)2;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Rdiv) {
    csp::array<TypeParam> arr = {{(TypeParam)1, (TypeParam)2, (TypeParam)-3, (TypeParam)-6},
                                 {(TypeParam)6, (TypeParam)3, (TypeParam)-4, (TypeParam)2}};
    auto b = arr.reciprocal((TypeParam)12); // 2.0 / arr
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)12, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Maximum) {
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr.maximum((TypeParam)1);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)2,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2,  AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOpWithAValue,Minimum) {
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr.minimum((TypeParam)1);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1,  AbsTol<TypeParam>::val);
  }

  TYPED_TEST(BinaryOpWithAValueCmp,Gt) {
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr > (TypeParam)2;
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
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr >= (TypeParam)2;
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
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr < (TypeParam)-4;
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
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr <= (TypeParam)-4;
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
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr == (TypeParam)-4;
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
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr != (TypeParam)-4;
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
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    arr += (TypeParam)3;
    EXPECT_NEAR(arr[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[6], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[7], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Sub) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    b -= (TypeParam)3;
    EXPECT_NEAR(b[0], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)-1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Mult) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    b *= (TypeParam)2;
    EXPECT_NEAR(b[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Div) {
    csp::array<TypeParam> b = {{(TypeParam)30, (TypeParam)4, (TypeParam)-50, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    b /= (TypeParam)2;
    EXPECT_NEAR(b[0], (TypeParam)15, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-25, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Rdiv) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-6, (TypeParam)-2},
                               {(TypeParam)1, (TypeParam)6, (TypeParam)-4, (TypeParam)2}};
    b.reciprocal_((TypeParam)12);
    EXPECT_NEAR(b[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)12, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Maximum) {
    csp::array<TypeParam> b = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    std::vector<int> bshape = b.shape();
    int bsize = b.size();
    b.maximum_((TypeParam)1);
    EXPECT_EQ(b.shape(), bshape);
    EXPECT_EQ(b.size(), bsize);
    EXPECT_NEAR(b[0], (TypeParam)2,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2,  AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOpWithAValue,Minimum) {
    csp::array<TypeParam> b = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    std::vector<int> bshape = b.shape();
    int bsize = b.size();
    b.minimum_((TypeParam)1);
    EXPECT_EQ(b.shape(), bshape);
    EXPECT_EQ(b.size(), bsize);
    EXPECT_NEAR(b[0], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0,  AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1,  AbsTol<TypeParam>::val);
  }

  // binary op with another array
  TYPED_TEST(BinaryOp,Add) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr + ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Sub) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr - ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Mult) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr * ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-25, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Div) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)1, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr / ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Aliasing) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    b = b + ars;
    EXPECT_EQ(b.shape(), ars.shape());
    EXPECT_EQ(b.size(), ars.size());
    EXPECT_NEAR(b[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Maximum) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr.maximum(ars);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Minimum) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr.minimum(ars);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(BinaryOp,Gt) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
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
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr >= ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], true);
  }
  TYPED_TEST(BinaryOp,Lt) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr < ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], false);
    EXPECT_EQ(b[5], true);
    EXPECT_EQ(b[6], true);
    EXPECT_EQ(b[7], false);
  }
  TYPED_TEST(BinaryOp,LtEq) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
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
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr == ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], false);
    EXPECT_EQ(b[1], false);
    EXPECT_EQ(b[2], false);
    EXPECT_EQ(b[3], false);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b[5], false);
    EXPECT_EQ(b[6], false);
    EXPECT_EQ(b[7], false);
  }
  TYPED_TEST(BinaryOp,NEq) {
    csp::array<TypeParam> arr = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    auto b = arr != ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[1], true);
    EXPECT_EQ(b[2], true);
    EXPECT_EQ(b[3], true);
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
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    b.fill_((TypeParam)1);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Add) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    b += ars;
    EXPECT_NEAR(b[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Sub) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    b -= ars;
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-10, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)1, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Mult) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)0, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    b *= ars;
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-25, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceBinaryOp,Div) {
    csp::array<TypeParam> b = {{(TypeParam)3, (TypeParam)4, (TypeParam)-5, (TypeParam)0},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    csp::array<TypeParam> ars = {{(TypeParam)1, (TypeParam)2, (TypeParam)5, (TypeParam)1},
                                 {(TypeParam)2, (TypeParam)2, (TypeParam)2, (TypeParam)1}};
    b /= ars;
    EXPECT_NEAR(b[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }

  // ternary op
  TYPED_TEST(TernaryOpWithValues,Clip) {
    csp::array<TypeParam> arr = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                                 {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    auto b = arr.clip((TypeParam)-1, (TypeParam)3);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(InplaceTernaryOpWithValues,Clip) {
    csp::array<TypeParam> b = {{(TypeParam)2, (TypeParam)4, (TypeParam)-5, (TypeParam)10},
                               {(TypeParam)0, (TypeParam)0, (TypeParam)-4, (TypeParam)2}};
    b.clip_((TypeParam)-1, (TypeParam)3);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)0, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[6], (TypeParam)-1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[7], (TypeParam)2, AbsTol<TypeParam>::val);
  }
}
#endif
