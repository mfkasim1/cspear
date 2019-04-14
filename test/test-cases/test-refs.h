#ifndef CSPEAR_TEST_TEST_CASES_TEST_REFS_H
#define CSPEAR_TEST_TEST_CASES_TEST_REFS_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  TEST(RefsTest,ReshapeAfterAtView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.at(0).reshape_({2,2});

    std::vector<int> shape = {2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 7.2);
    EXPECT_DOUBLE_EQ(b[1], 3.4);
    EXPECT_DOUBLE_EQ(b[2], 5.6);
    EXPECT_DOUBLE_EQ(b[3], 1.0);
  }
  TEST(RefsTest,ReshapeAfterFilterView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.filter(a <= 3.5).reshape_({2,2});

    std::vector<int> shape = {2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 3.4);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 2.1);
    EXPECT_DOUBLE_EQ(b[3], 1.3);
  }
  TEST(RefsTest,ReshapeAfterIndexView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.take({1,3,5,7}).reshape_({2,2});

    std::vector<int> shape = {2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 3.4);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 2.1);
    EXPECT_DOUBLE_EQ(b[3], 1.3);
  }

  TEST(RefsTest,InplaceOpAfterAtView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.at(0).add_(1.0);

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 8.2);
    EXPECT_DOUBLE_EQ(b[1], 4.4);
    EXPECT_DOUBLE_EQ(b[2], 6.6);
    EXPECT_DOUBLE_EQ(b[3], 2.0);
  }
  TEST(RefsTest,InplaceOpAfterFilterView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.filter(a <= 3.5).add_(1.0);

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 4.4);
    EXPECT_DOUBLE_EQ(b[1], 2.0);
    EXPECT_DOUBLE_EQ(b[2], 3.1);
    EXPECT_DOUBLE_EQ(b[3], 2.3);
  }
  TEST(RefsTest,InplaceOpAfterIndexView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.take({1,3,5,7}).add_(1.0);

    std::vector<int> shape = {4};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 4.4);
    EXPECT_DOUBLE_EQ(b[1], 2.0);
    EXPECT_DOUBLE_EQ(b[2], 3.1);
    EXPECT_DOUBLE_EQ(b[3], 2.3);
  }
  TEST(RefsTest,InplaceOpAfterSliceView) {
    csp::array<double> a = {{7.2, 3.4, 5.6, 1.0}, {4.1, 2.1, 4.2, 1.3}};
    auto b = a.slice({{0,2},{1,3}}).add_(1.0);

    std::vector<int> shape = {2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 4.4);
    EXPECT_DOUBLE_EQ(b[1], 6.6);
    EXPECT_DOUBLE_EQ(b[2], 3.1);
    EXPECT_DOUBLE_EQ(b[3], 5.2);
  }
}

#endif
