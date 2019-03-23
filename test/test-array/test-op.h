#ifndef CSPEAR_TEST_ARRAY_TEST_OP_H
#define CSPEAR_TEST_ARRAY_TEST_OP_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  TEST(UnaryOp,Neg) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = -arr;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_EQ(b[0], -3.0);
    EXPECT_EQ(b[1], -4.1);
    EXPECT_EQ(b[2], 5.0);
    EXPECT_EQ(b[3], 0.0);
    EXPECT_EQ(b[4], -0.1);
    EXPECT_EQ(b[5], -0.2);
    EXPECT_EQ(b[6], 4.1);
    EXPECT_EQ(b[7], -2.1);
  }
  TEST(BinaryOpWithAValue,Add) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr + 3.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 6.0);
    EXPECT_DOUBLE_EQ(b[1], 7.1);
    EXPECT_DOUBLE_EQ(b[2], -2.0);
    EXPECT_DOUBLE_EQ(b[3], 3.0);
    EXPECT_DOUBLE_EQ(b[4], 3.1);
    EXPECT_DOUBLE_EQ(b[5], 3.2);
    EXPECT_DOUBLE_EQ(b[6], -1.1);
    EXPECT_DOUBLE_EQ(b[7], 5.1);
  }
  TEST(BinaryOpWithAValue,Sub) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr - 3.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 0.0);
    EXPECT_DOUBLE_EQ(b[1], 1.1);
    EXPECT_DOUBLE_EQ(b[2], -8.0);
    EXPECT_DOUBLE_EQ(b[3], -3.0);
    EXPECT_DOUBLE_EQ(b[4], -2.9);
    EXPECT_DOUBLE_EQ(b[5], -2.8);
    EXPECT_DOUBLE_EQ(b[6], -7.1);
    EXPECT_DOUBLE_EQ(b[7], -0.9);
  }
  TEST(BinaryOpWithAValue,Mult) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr * 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 6.0);
    EXPECT_DOUBLE_EQ(b[1], 8.2);
    EXPECT_DOUBLE_EQ(b[2], -10.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.2);
    EXPECT_DOUBLE_EQ(b[5], 0.4);
    EXPECT_DOUBLE_EQ(b[6], -8.2);
    EXPECT_DOUBLE_EQ(b[7], 4.2);
  }
  TEST(BinaryOpWithAValue,Div) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    auto b = arr / 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 1.5);
    EXPECT_DOUBLE_EQ(b[1], 2.05);
    EXPECT_DOUBLE_EQ(b[2], -2.5);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.05);
    EXPECT_DOUBLE_EQ(b[5], 0.1);
    EXPECT_DOUBLE_EQ(b[6], -2.05);
    EXPECT_DOUBLE_EQ(b[7], 1.05);
  }
  TEST(BinaryOpWithAValue,Rdiv) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.reciprocal(2.0); // 2.0 / arr
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 0.5);
    EXPECT_DOUBLE_EQ(b[2], -0.4);
    EXPECT_DOUBLE_EQ(b[3], 0.2);
    EXPECT_DOUBLE_EQ(b[4], 20.0);
    EXPECT_DOUBLE_EQ(b[5], 10.0);
    EXPECT_DOUBLE_EQ(b[6], -0.5);
    EXPECT_DOUBLE_EQ(b[7], 1.0);
  }
  TEST(BinaryOpWithAValue,ClipLb) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip_lb(2.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 4.0);
    EXPECT_DOUBLE_EQ(b[2], 2.0);
    EXPECT_DOUBLE_EQ(b[3], 10.0);
    EXPECT_DOUBLE_EQ(b[4], 2.0);
    EXPECT_DOUBLE_EQ(b[5], 2.0);
    EXPECT_DOUBLE_EQ(b[6], 2.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
  }
  TEST(BinaryOpWithAValue,ClipUb) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip_ub(2.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 2.0);
    EXPECT_DOUBLE_EQ(b[2], -5.0);
    EXPECT_DOUBLE_EQ(b[3], 2.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.2);
    EXPECT_DOUBLE_EQ(b[6], -4.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
  }
  TEST(BinaryOpWithAValue,Clip) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr.clip(-1.0, 3.0);
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 3.0);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], 3.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.2);
    EXPECT_DOUBLE_EQ(b[6], -1.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
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
  TEST(BinaryOpWithAValueBool,Gt) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr > 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOpWithAValueBool,GtEq) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr >= 2.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], true);
  }
  TEST(BinaryOpWithAValueBool,Lt) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr < -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOpWithAValueBool,LtEq) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr <= -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], true);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOpWithAValueBool,Eq) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr == -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], true);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOpWithAValueBool,NEq) {
    csp::array<double> arr = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    auto b = arr != -4.0;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], true);
  }
  TEST(BinaryOpWithAValueBool,And) {
    csp::array<bool> arr = {{true, false, true}, {false, false, true}};
    auto b = arr && true;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], true);
    auto c = arr && false;
    EXPECT_EQ(c.shape(), arr.shape());
    EXPECT_EQ(c.size(), arr.size());
    EXPECT_DOUBLE_EQ(c[0], false);
    EXPECT_DOUBLE_EQ(c[1], false);
    EXPECT_DOUBLE_EQ(c[2], false);
    EXPECT_DOUBLE_EQ(c[3], false);
    EXPECT_DOUBLE_EQ(c[4], false);
    EXPECT_DOUBLE_EQ(c[5], false);
  }
  TEST(BinaryOpWithAValueBool,Or) {
    csp::array<bool> arr = {{true, false, true}, {false, false, true}};
    auto b = arr || false;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], true);
    auto c = arr || true;
    EXPECT_EQ(c.shape(), arr.shape());
    EXPECT_EQ(c.size(), arr.size());
    EXPECT_DOUBLE_EQ(c[0], true);
    EXPECT_DOUBLE_EQ(c[1], true);
    EXPECT_DOUBLE_EQ(c[2], true);
    EXPECT_DOUBLE_EQ(c[3], true);
    EXPECT_DOUBLE_EQ(c[4], true);
    EXPECT_DOUBLE_EQ(c[5], true);
  }

  TEST(InplaceBinaryOpWithAValue,Add) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    arr += 3.0;
    EXPECT_DOUBLE_EQ(arr[0], 6.0);
    EXPECT_DOUBLE_EQ(arr[1], 7.1);
    EXPECT_DOUBLE_EQ(arr[2], -2.0);
    EXPECT_DOUBLE_EQ(arr[3], 3.0);
    EXPECT_DOUBLE_EQ(arr[4], 3.1);
    EXPECT_DOUBLE_EQ(arr[5], 3.2);
    EXPECT_DOUBLE_EQ(arr[6], -1.1);
    EXPECT_DOUBLE_EQ(arr[7], 5.1);
  }
  TEST(InplaceBinaryOpWithAValue,Sub) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b -= 3.0;
    EXPECT_DOUBLE_EQ(b[0], 0.0);
    EXPECT_DOUBLE_EQ(b[1], 1.1);
    EXPECT_DOUBLE_EQ(b[2], -8.0);
    EXPECT_DOUBLE_EQ(b[3], -3.0);
    EXPECT_DOUBLE_EQ(b[4], -2.9);
    EXPECT_DOUBLE_EQ(b[5], -2.8);
    EXPECT_DOUBLE_EQ(b[6], -7.1);
    EXPECT_DOUBLE_EQ(b[7], -0.9);
  }
  TEST(InplaceBinaryOpWithAValue,Mult) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b *= 2.0;
    EXPECT_DOUBLE_EQ(b[0], 6.0);
    EXPECT_DOUBLE_EQ(b[1], 8.2);
    EXPECT_DOUBLE_EQ(b[2], -10.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.2);
    EXPECT_DOUBLE_EQ(b[5], 0.4);
    EXPECT_DOUBLE_EQ(b[6], -8.2);
    EXPECT_DOUBLE_EQ(b[7], 4.2);
  }
  TEST(InplaceBinaryOpWithAValue,Div) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    b /= 2.0;
    EXPECT_DOUBLE_EQ(b[0], 1.5);
    EXPECT_DOUBLE_EQ(b[1], 2.05);
    EXPECT_DOUBLE_EQ(b[2], -2.5);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.05);
    EXPECT_DOUBLE_EQ(b[5], 0.1);
    EXPECT_DOUBLE_EQ(b[6], -2.05);
    EXPECT_DOUBLE_EQ(b[7], 1.05);
  }
  TEST(InplaceBinaryOpWithAValue,Rdiv) {
    csp::array<double> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.reciprocal_(2.0);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 0.5);
    EXPECT_DOUBLE_EQ(b[2], -0.4);
    EXPECT_DOUBLE_EQ(b[3], 0.2);
    EXPECT_DOUBLE_EQ(b[4], 20.0);
    EXPECT_DOUBLE_EQ(b[5], 10.0);
    EXPECT_DOUBLE_EQ(b[6], -0.5);
    EXPECT_DOUBLE_EQ(b[7], 1.0);
  }
  TEST(InplaceBinaryOpWithAValue,ClipLb) {
    csp::array<double> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_lb_(2.0);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 4.0);
    EXPECT_DOUBLE_EQ(b[2], 2.0);
    EXPECT_DOUBLE_EQ(b[3], 10.0);
    EXPECT_DOUBLE_EQ(b[4], 2.0);
    EXPECT_DOUBLE_EQ(b[5], 2.0);
    EXPECT_DOUBLE_EQ(b[6], 2.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
  }
  TEST(InplaceBinaryOpWithAValue,ClipUb) {
    csp::array<double> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_ub_(2.0);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 2.0);
    EXPECT_DOUBLE_EQ(b[2], -5.0);
    EXPECT_DOUBLE_EQ(b[3], 2.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.2);
    EXPECT_DOUBLE_EQ(b[6], -4.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
  }
  TEST(InplaceBinaryOpWithAValue,Clip) {
    csp::array<double> b = {{2.0, 4.0, -5.0, 10.0}, {0.1, 0.2, -4.0, 2.0}};
    b.clip_(-1.0, 3.0);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 3.0);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], 3.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.2);
    EXPECT_DOUBLE_EQ(b[6], -1.0);
    EXPECT_DOUBLE_EQ(b[7], 2.0);
  }
}

  // binary op with another array
  TEST(BinaryOp,Add) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr + ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 4.0);
    EXPECT_DOUBLE_EQ(b[1], 6.1);
    EXPECT_DOUBLE_EQ(b[2], 0.0);
    EXPECT_DOUBLE_EQ(b[3], 1.1);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 2.2);
    EXPECT_DOUBLE_EQ(b[6], -2.1);
    EXPECT_DOUBLE_EQ(b[7], 3.1);
  }
  TEST(BinaryOp,Sub) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr - ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 2.1);
    EXPECT_DOUBLE_EQ(b[2], -10.0);
    EXPECT_DOUBLE_EQ(b[3], -1.1);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], -1.8);
    EXPECT_DOUBLE_EQ(b[6], -6.1);
    EXPECT_DOUBLE_EQ(b[7], 1.1);
  }
  TEST(BinaryOp,Mult) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    auto b = arr * ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 8.2);
    EXPECT_DOUBLE_EQ(b[2], -25.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.0);
    EXPECT_DOUBLE_EQ(b[5], 0.4);
    EXPECT_DOUBLE_EQ(b[6], -8.2);
    EXPECT_DOUBLE_EQ(b[7], 2.1);
  }
  TEST(BinaryOp,Div) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr / ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 2.05);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.1);
    EXPECT_DOUBLE_EQ(b[6], -2.05);
    EXPECT_DOUBLE_EQ(b[7], 2.1);
  }
  TEST(BinaryOp,Gt) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr > ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], true);
  }
  TEST(BinaryOp,GtEq) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr >= ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], true);
  }
  TEST(BinaryOp,Lt) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr < ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], true);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOp,LtEq) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    auto b = arr <= ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], true);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOp,Eq) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 0.0}, {0.1, 2.0, 2.0, 1.0}};
    auto b = arr == ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], false);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], true);
    EXPECT_DOUBLE_EQ(b[3], true);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], false);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOp,NEq) {
    csp::array<double> arr = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, -5.0, 0.0}, {0.1, 2.0, 2.0, 1.0}};
    auto b = arr != ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], false);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], true);
    EXPECT_DOUBLE_EQ(b[7], true);
  }
  TEST(BinaryOpBool,And) {
    csp::array<bool> arr = {{true, true, false, false}, {true, true, false, false}};
    csp::array<bool> ars = {{true, false, false, false}, {true, true, false, true}};
    auto b = arr && ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], false);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], false);
  }
  TEST(BinaryOpBool,Or) {
    csp::array<bool> arr = {{true, true, false, false}, {true, true, false, false}};
    csp::array<bool> ars = {{true, false, false, false}, {true, true, false, true}};
    auto b = arr || ars;
    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_EQ(b.size(), arr.size());
    EXPECT_DOUBLE_EQ(b[0], true);
    EXPECT_DOUBLE_EQ(b[1], true);
    EXPECT_DOUBLE_EQ(b[2], false);
    EXPECT_DOUBLE_EQ(b[3], false);
    EXPECT_DOUBLE_EQ(b[4], true);
    EXPECT_DOUBLE_EQ(b[5], true);
    EXPECT_DOUBLE_EQ(b[6], false);
    EXPECT_DOUBLE_EQ(b[7], true);
  }

  // inplace binary operator with another array
  TEST(InplaceBinaryOp,Add) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b += ars;
    EXPECT_DOUBLE_EQ(b[0], 4.0);
    EXPECT_DOUBLE_EQ(b[1], 6.1);
    EXPECT_DOUBLE_EQ(b[2], 0.0);
    EXPECT_DOUBLE_EQ(b[3], 1.1);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 2.2);
    EXPECT_DOUBLE_EQ(b[6], -2.1);
    EXPECT_DOUBLE_EQ(b[7], 3.1);
  }
  TEST(InplaceBinaryOp,Sub) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b -= ars;
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 2.1);
    EXPECT_DOUBLE_EQ(b[2], -10.0);
    EXPECT_DOUBLE_EQ(b[3], -1.1);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], -1.8);
    EXPECT_DOUBLE_EQ(b[6], -6.1);
    EXPECT_DOUBLE_EQ(b[7], 1.1);
  }
  TEST(InplaceBinaryOp,Mult) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.1}, {0.0, 2.0, 2.0, 1.0}};
    b *= ars;
    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 8.2);
    EXPECT_DOUBLE_EQ(b[2], -25.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.0);
    EXPECT_DOUBLE_EQ(b[5], 0.4);
    EXPECT_DOUBLE_EQ(b[6], -8.2);
    EXPECT_DOUBLE_EQ(b[7], 2.1);
  }
  TEST(InplaceBinaryOp,Div) {
    csp::array<double> b = {{3.0, 4.1, -5.0, 0.0}, {0.1, 0.2, -4.1, 2.1}};
    csp::array<double> ars = {{1.0, 2.0, 5.0, 1.0}, {1.0, 2.0, 2.0, 1.0}};
    b /= ars;
    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 2.05);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], 0.0);
    EXPECT_DOUBLE_EQ(b[4], 0.1);
    EXPECT_DOUBLE_EQ(b[5], 0.1);
    EXPECT_DOUBLE_EQ(b[6], -2.05);
    EXPECT_DOUBLE_EQ(b[7], 2.1);
  }
#endif
