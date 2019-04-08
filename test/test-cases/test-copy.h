#ifndef TEST_TEST_CASES_TEST_COPY_H
#define TEST_TEST_CASES_TEST_COPY_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  TEST(CopyCases,CopyAndFilter) {
    csp::array<double> a = {{7.2, 3.4, 5.6}, {2.1, 4.2, 1.3}};
    csp::array<double> b;
    auto c = a.at(0);
    b = c.copy();

    c.filter(c > 6.0) += 1;
    EXPECT_DOUBLE_EQ(a[0], 8.2);
    EXPECT_DOUBLE_EQ(b[0], 7.2);
  }
  TEST(CopyCases,ViewAndCopy) {
    csp::array<double> a = {{7.2, 3.4, 5.6}, {2.1, 4.2, 1.3}};
    // new memory is made by .copy(), but only part of it is used by .at(0)
    auto b = a.copy().at(0);
    std::vector<int> shape = {3};
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(b.size(), 3);
    EXPECT_DOUBLE_EQ(b[0], 7.2);
    EXPECT_DOUBLE_EQ(b[1], 3.4);
    EXPECT_DOUBLE_EQ(b[2], 5.6);

    auto c = a.filter(a < 7.0).copy().at(0);
    std::vector<int> shape2 = {1};
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_EQ(c.size(), 1);
    EXPECT_DOUBLE_EQ(c[0], 3.4);
  }
}

#endif
