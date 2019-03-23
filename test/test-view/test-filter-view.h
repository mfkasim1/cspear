#ifndef CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  TEST(FilterView,FromContiguous) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto b = a[a < 3.1];

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 3.0);
    EXPECT_DOUBLE_EQ(b[2], 2.1);
  }
  TEST(FilterView,InplaceAddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a[a < 3.1] += 2.0;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 3.0);
    EXPECT_DOUBLE_EQ(a[1], 4.2);
    EXPECT_DOUBLE_EQ(a[2], 5.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 4.1);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(FilterView,InplaceAddArray) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> b = {2.0, 6.0, 4.2};
    a[a < 3.1] += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 3.0);
    EXPECT_DOUBLE_EQ(a[1], 4.2);
    EXPECT_DOUBLE_EQ(a[2], 9.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 6.3);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(FilterView,InplaceClip) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a[a < 3.1].clip_lb_(2.5);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.5);
    EXPECT_DOUBLE_EQ(a[1], 4.2);
    EXPECT_DOUBLE_EQ(a[2], 3.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 2.5);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(FilterView,AddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto c = a[a < 3.1] + 2.0;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_DOUBLE_EQ(c[0], 3.0);
    EXPECT_DOUBLE_EQ(c[1], 5.0);
    EXPECT_DOUBLE_EQ(c[2], 4.1);
  }
  TEST(FilterView,AddArray) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> b = {2.0, 6.0, 4.2};
    auto c = a[a < 3.1] + b;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_DOUBLE_EQ(c[0], 3.0);
    EXPECT_DOUBLE_EQ(c[1], 9.0);
    EXPECT_DOUBLE_EQ(c[2], 6.3);
  }
  TEST(FilterView,MismatchShape) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> b = {2.0, 6.0, 4.2};
    try {
      auto c = a[b > 2.1];
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
  }
}

#endif
