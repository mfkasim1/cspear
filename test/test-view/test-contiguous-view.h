#ifndef CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  // test accessing the first dimension
  TEST(ContiguousViewSingleElmt,FromContiguous1D) {
    csp::array<double> a = {1.0, 4.2, 3.0};
    auto b = a(0);
    auto c = a(1);

    std::vector<int> shape = {1};
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(c[0], 4.2);
  }
  TEST(ContiguousViewSingleElmt,FromContiguous2D) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto b = a(0);
    auto c = a(1);

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 4.2);
    EXPECT_DOUBLE_EQ(b[2], 3.0);
    EXPECT_DOUBLE_EQ(c[0], 6.9);
    EXPECT_DOUBLE_EQ(c[1], 2.1);
    EXPECT_DOUBLE_EQ(c[2], 5.2);
  }
  TEST(ContiguousViewSingleElmt,FromContiguous2DError) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    try {
      auto b = a(2);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }

    try {
      auto b = a(-1);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
  }
  TEST(ContiguousViewSingleElmt,InplaceAddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a(0) += 1.0;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.0);
    EXPECT_DOUBLE_EQ(a[1], 5.2);
    EXPECT_DOUBLE_EQ(a[2], 4.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 2.1);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(ContiguousViewSingleElmt,InplaceAddArray) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> b = {1.0, 2.0, 4.0};
    a(0) += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.0);
    EXPECT_DOUBLE_EQ(a[1], 6.2);
    EXPECT_DOUBLE_EQ(a[2], 7.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 2.1);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(ContiguousViewSingleElmt,InplaceClip) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a(0).clip_lb_(3.5);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 3.5);
    EXPECT_DOUBLE_EQ(a[1], 4.2);
    EXPECT_DOUBLE_EQ(a[2], 3.5);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 2.1);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
  TEST(ContiguousViewSingleElmt,AddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    auto b = a(0) + 1.0;

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 5.2);
    EXPECT_DOUBLE_EQ(b[2], 4.0);
  }
  TEST(ContiguousViewSingleElmt,AddArray) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> c = {1.0, 2.0, 3.0};
    auto b = a(0) + c;

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 6.2);
    EXPECT_DOUBLE_EQ(b[2], 6.0);
  }
  TEST(ContiguousViewSingleElmt,AddArrayBCast) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> c = {1.0, 2.0, 3.0};
    auto b = a(0) + c(0); // c(0) is {1.0}

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 5.2);
    EXPECT_DOUBLE_EQ(b[2], 4.0);
  }
  TEST(ContiguousViewSingleElmt,Assignment) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    csp::array<double> c = {1.0, 2.0, 3.0};
    a(0) = c;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 1.0);
    EXPECT_DOUBLE_EQ(a[1], 2.0);
    EXPECT_DOUBLE_EQ(a[2], 3.0);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 2.1);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
  }
}

#endif
