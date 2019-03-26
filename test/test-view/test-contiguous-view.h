#ifndef CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  // test accessing the first dimension
  TEST(ContiguousViewSingleElmt,FromContiguous1D) {
    csp::array<double> a = {1.0, 4.2, 3.0};
    auto b = a.at(0);
    auto c = a.at(1);

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
    auto b = a.at(0);
    auto c = a.at(1);

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
      auto b = a.at(2);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }

    try {
      auto b = a.at(-1);
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
    a.at(0) += 1.0;

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
    a.at(0) += b;

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
    a.at(0).clip_lb_(3.5);

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
    auto b = a.at(0) + 1.0;

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
    auto b = a.at(0) + c;

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
    auto b = a.at(0) + c.at(0); // c.at(0) is {1.0}

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
    a.at(0) = c;

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
  TEST(ContiguousViewSingleElmt,Aliasing1) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    a += a.at(0);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.0);
    EXPECT_DOUBLE_EQ(a[1], 8.4);
    EXPECT_DOUBLE_EQ(a[2], 6.0);
    EXPECT_DOUBLE_EQ(a[3], 7.9);
    EXPECT_DOUBLE_EQ(a[4], 6.3);
    EXPECT_DOUBLE_EQ(a[5], 8.2);
  }

  // accessing a slice from the first dimension
  TEST(ContiguousViewMultiElmt,FromContiguous1D) {
    csp::array<double> a = {1.0, 4.2, 3.0};
    auto b = a.at(0,1);
    auto c = a.at(0,2);

    std::vector<int> shape1 = {1};
    std::vector<int> shape2 = {2};
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b.shape(), shape1);
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(c[0], 1.0);
    EXPECT_DOUBLE_EQ(c[1], 4.2);
  }
  TEST(ContiguousViewMultiElmt,FromContiguous2D) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    auto b = a.at(0,1);
    auto c = a.at(1,3);

    std::vector<int> shape = {1,3};
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 6);
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 4.2);
    EXPECT_DOUBLE_EQ(b[2], 3.0);
    EXPECT_DOUBLE_EQ(c[0], 6.9);
    EXPECT_DOUBLE_EQ(c[1], 2.1);
    EXPECT_DOUBLE_EQ(c[2], 5.2);
    EXPECT_DOUBLE_EQ(c[3], 1.0);
    EXPECT_DOUBLE_EQ(c[4], 9.0);
    EXPECT_DOUBLE_EQ(c[5], 3.0);
  }
  TEST(ContiguousViewMultiElmt,FromContiguous2DError) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}};
    try {
      auto b = a.at(0,3);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }

    try {
      auto b = a.at(-1,1);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
  }
  TEST(ContiguousViewMultiElmt,InplaceAddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    a.at(0,2) += 1.0;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.0);
    EXPECT_DOUBLE_EQ(a[1], 5.2);
    EXPECT_DOUBLE_EQ(a[2], 4.0);
    EXPECT_DOUBLE_EQ(a[3], 7.9);
    EXPECT_DOUBLE_EQ(a[4], 3.1);
    EXPECT_DOUBLE_EQ(a[5], 6.2);
    EXPECT_DOUBLE_EQ(a[6], 1.0);
    EXPECT_DOUBLE_EQ(a[7], 9.0);
    EXPECT_DOUBLE_EQ(a[8], 3.0);
  }
  TEST(ContiguousViewMultiElmt,InplaceAddArray) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    csp::array<double> b = {1.0, 2.0, 4.0};
    a.at(0,2) += b;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 2.0);
    EXPECT_DOUBLE_EQ(a[1], 6.2);
    EXPECT_DOUBLE_EQ(a[2], 7.0);
    EXPECT_DOUBLE_EQ(a[3], 7.9);
    EXPECT_DOUBLE_EQ(a[4], 4.1);
    EXPECT_DOUBLE_EQ(a[5], 9.2);
    EXPECT_DOUBLE_EQ(a[6], 1.0);
    EXPECT_DOUBLE_EQ(a[7], 9.0);
    EXPECT_DOUBLE_EQ(a[8], 3.0);
  }
  TEST(ContiguousViewMultiElmt,InplaceClip) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    a.at(0,2).clip_lb_(3.5);

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 3.5);
    EXPECT_DOUBLE_EQ(a[1], 4.2);
    EXPECT_DOUBLE_EQ(a[2], 3.5);
    EXPECT_DOUBLE_EQ(a[3], 6.9);
    EXPECT_DOUBLE_EQ(a[4], 3.5);
    EXPECT_DOUBLE_EQ(a[5], 5.2);
    EXPECT_DOUBLE_EQ(a[6], 1.0);
    EXPECT_DOUBLE_EQ(a[7], 9.0);
    EXPECT_DOUBLE_EQ(a[8], 3.0);
  }
  TEST(ContiguousViewMultiElmt,AddAValue) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    auto b = a.at(0,2) + 1.0;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 5.2);
    EXPECT_DOUBLE_EQ(b[2], 4.0);
    EXPECT_DOUBLE_EQ(b[3], 7.9);
    EXPECT_DOUBLE_EQ(b[4], 3.1);
    EXPECT_DOUBLE_EQ(b[5], 6.2);
  }
  TEST(ContiguousViewMultiElmt,AddArrayBCast) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    csp::array<double> c = {1.0, 2.0, 3.0};
    auto b = a.at(0,2) + c;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_DOUBLE_EQ(b[0], 2.0);
    EXPECT_DOUBLE_EQ(b[1], 6.2);
    EXPECT_DOUBLE_EQ(b[2], 6.0);
    EXPECT_DOUBLE_EQ(b[3], 7.9);
    EXPECT_DOUBLE_EQ(b[4], 4.1);
    EXPECT_DOUBLE_EQ(b[5], 8.2);
  }
  TEST(ContiguousViewMultiElmt,Assignment) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    csp::array<double> c = {1.0, 2.0, 3.0};
    a.at(0,2) = c;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 1.0);
    EXPECT_DOUBLE_EQ(a[1], 2.0);
    EXPECT_DOUBLE_EQ(a[2], 3.0);
    EXPECT_DOUBLE_EQ(a[3], 1.0);
    EXPECT_DOUBLE_EQ(a[4], 2.0);
    EXPECT_DOUBLE_EQ(a[5], 3.0);
    EXPECT_DOUBLE_EQ(a[6], 1.0);
    EXPECT_DOUBLE_EQ(a[7], 9.0);
    EXPECT_DOUBLE_EQ(a[8], 3.0);
  }
  TEST(ContiguousViewMultiElmt,Aliasing1) {
    csp::array<double> a = {{1.0, 4.2, 3.0}, {6.9, 2.1, 5.2}, {1.0, 9.0, 3.0}};
    a.at(0,2) = a.at(1,3);

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_DOUBLE_EQ(a[0], 6.9);
    EXPECT_DOUBLE_EQ(a[1], 2.1);
    EXPECT_DOUBLE_EQ(a[2], 5.2);
    EXPECT_DOUBLE_EQ(a[3], 1.0);
    EXPECT_DOUBLE_EQ(a[4], 9.0);
    EXPECT_DOUBLE_EQ(a[5], 3.0);
    EXPECT_DOUBLE_EQ(a[6], 1.0);
    EXPECT_DOUBLE_EQ(a[7], 9.0);
    EXPECT_DOUBLE_EQ(a[8], 3.0);
  }
}

#endif
