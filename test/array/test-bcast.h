#ifndef CSPEAR_TEST_ARRAY_BCAST_H
#define CSPEAR_TEST_ARRAY_BCAST_H

#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  // broadcast test for the shapes
  TEST(BCastOp,Add1) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<double> ars = {1.0};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 3.1);
    EXPECT_DOUBLE_EQ(b[2], 4.2);
    EXPECT_DOUBLE_EQ(b[3], 9.2);
    EXPECT_DOUBLE_EQ(b[4], 8.1);
    EXPECT_DOUBLE_EQ(b[5], -3.5);
  }
  TEST(BCastOp,Add2) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<double> ars = {1.0, 2.0, 4.0};
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 4.1);
    EXPECT_DOUBLE_EQ(b[2], 7.2);
    EXPECT_DOUBLE_EQ(b[3], 9.2);
    EXPECT_DOUBLE_EQ(b[4], 9.1);
    EXPECT_DOUBLE_EQ(b[5], -0.5);
  }
  TEST(BCastOp,Add3) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}, {8.2, 7.1, -4.5}};
    csp::array<double> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr + ars;

    EXPECT_EQ(b.shape(), arr.shape());
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 3.1);
    EXPECT_DOUBLE_EQ(b[2], 4.2);
    EXPECT_DOUBLE_EQ(b[3], 10.2);
    EXPECT_DOUBLE_EQ(b[4], 9.1);
    EXPECT_DOUBLE_EQ(b[5], -2.5);
  }
  TEST(BCastOp,Add4) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}};
    csp::array<double> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr + ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 3.1);
    EXPECT_DOUBLE_EQ(b[2], 4.2);
    EXPECT_DOUBLE_EQ(b[3], 3.0);
    EXPECT_DOUBLE_EQ(b[4], 4.1);
    EXPECT_DOUBLE_EQ(b[5], 5.2);
  }
  TEST(BCastOp,Add5) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}, {3.1, 3.0, 2.1}};
    csp::array<double> ars = {1.0, 2.0};
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
  TEST(BCastOp,Sub) {
    csp::array<double> arr = {{1.0, 2.0, 3.2}};
    csp::array<double> ars = {1.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr - ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 0.0);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 2.2);
    EXPECT_DOUBLE_EQ(b[3], -1.0);
    EXPECT_DOUBLE_EQ(b[4], 0.0);
    EXPECT_DOUBLE_EQ(b[5], 1.2);
  }
  TEST(BCastOp,Mult) {
    csp::array<double> arr = {{1.0, 2.1, 3.2}};
    csp::array<double> ars = {3.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr * ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 6.3);
    EXPECT_DOUBLE_EQ(b[2], 9.6);
    EXPECT_DOUBLE_EQ(b[3], 2.0);
    EXPECT_DOUBLE_EQ(b[4], 4.2);
    EXPECT_DOUBLE_EQ(b[5], 6.4);
  }
  TEST(BCastOp,Div) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {4.0, 2.0};
    ars.expand_dims_(1);
    auto b = arr / ars;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 0.25);
    EXPECT_DOUBLE_EQ(b[1], 0.5);
    EXPECT_DOUBLE_EQ(b[2], 0.75);
    EXPECT_DOUBLE_EQ(b[3], 0.5);
    EXPECT_DOUBLE_EQ(b[4], 1.0);
    EXPECT_DOUBLE_EQ(b[5], 1.5);
  }
  TEST(BCastOpBool,Gt) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
  TEST(BCastOpBool,GtEq) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
  TEST(BCastOpBool,Lt) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
  TEST(BCastOpBool,LtEq) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
  TEST(BCastOpBool,Eq) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
  TEST(BCastOpBool,NEq) {
    csp::array<double> arr = {{1.0, 2.0, 3.0}};
    csp::array<double> ars = {1.5, 2.0};
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
