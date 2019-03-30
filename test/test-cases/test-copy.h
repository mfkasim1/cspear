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
}

#endif
