#ifndef CSPEAR_TEST_ARRAY_TEST_REDUCE_H
#define CSPEAR_TEST_ARRAY_TEST_REDUCE_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  TEST(ReduceTest,SumAll) {
    csp::array<double> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    EXPECT_DOUBLE_EQ(arr.sum(), 29.0);
  }
  TEST(ReduceTest,SumAxis) {
    csp::array<double> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};

    auto arr0 = arr.sum(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_DOUBLE_EQ(arr0[0], 7.0);
    EXPECT_DOUBLE_EQ(arr0[1], 9.0);
    EXPECT_DOUBLE_EQ(arr0[2], 13.0);

    auto arr1 = arr.sum(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_DOUBLE_EQ(arr1[0], 7.0);
    EXPECT_DOUBLE_EQ(arr1[1], 22.0);
  }
  TEST(ReduceTest,SumAxes1) {
    csp::array<double> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.sum(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], 29.0);
  }
  TEST(ReduceTest,SumAxes2) {
    csp::array<double> arr = {{1.0, 2.0, 4.0}, {6.0, 7.0, 9.0}};
    auto arr0 = arr.sum({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], 29.0);
  }

  TEST(ReduceTest,MinAll) {
    csp::array<double> arr = {{10.0, 2.0, 14.0}, {6.0, 7.0, 9.0}};
    EXPECT_DOUBLE_EQ(arr.min(), 2.0);

    csp::array<double> arr1 = {{-10.0, 2.0, 14.0}, {-6.0, -7.0, 9.0}};
    EXPECT_DOUBLE_EQ(arr1.min(), -10.0);
  }
  TEST(ReduceTest,MinAxis) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};

    auto arr0 = arr.min(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_DOUBLE_EQ(arr0[0], -1.0);
    EXPECT_DOUBLE_EQ(arr0[1], -7.0);
    EXPECT_DOUBLE_EQ(arr0[2], -9.0);

    auto arr1 = arr.min(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_DOUBLE_EQ(arr1[0], -4.0);
    EXPECT_DOUBLE_EQ(arr1[1], -9.0);
  }
  TEST(ReduceTest,MinAxes1) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.min(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], -9.0);
  }
  TEST(ReduceTest,MinAxes2) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    auto arr0 = arr.min({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], -9.0);
  }

  TEST(ReduceTest,MaxAll) {
    csp::array<double> arr = {{10.0, 2.0, 14.0}, {6.0, 7.0, 9.0}};
    EXPECT_DOUBLE_EQ(arr.max(), 14.0);

    csp::array<double> arr1 = {{-10.0, -2.0, -14.0}, {-6.0, -7.0, -9.0}};
    EXPECT_DOUBLE_EQ(arr1.max(), -2.0);
  }
  TEST(ReduceTest,MaxAxis) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};

    auto arr0 = arr.max(0);
    std::vector<int> shape0 = {3};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 3);
    EXPECT_DOUBLE_EQ(arr0[0], 6.0);
    EXPECT_DOUBLE_EQ(arr0[1], 21.0);
    EXPECT_DOUBLE_EQ(arr0[2], -4.0);

    auto arr1 = arr.max(1);
    std::vector<int> shape1 = {2};
    EXPECT_EQ(arr1.shape(), shape1);
    EXPECT_EQ(arr1.size(), 2);
    EXPECT_DOUBLE_EQ(arr1[0], 21.0);
    EXPECT_DOUBLE_EQ(arr1[1], 6.0);
  }
  TEST(ReduceTest,MaxAxes1) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    std::vector<int> axes = {0,1};
    auto arr0 = arr.max(axes);
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], 21.0);
  }
  TEST(ReduceTest,MaxAxes2) {
    csp::array<double> arr = {{-1.0, 21.0, -4.0}, {6.0, -7.0, -9.0}};
    auto arr0 = arr.max({0,1});
    std::vector<int> shape0 = {1};
    EXPECT_EQ(arr0.shape(), shape0);
    EXPECT_EQ(arr0.size(), 1);
    EXPECT_DOUBLE_EQ(arr0[0], 21.0);
  }
}

#endif
