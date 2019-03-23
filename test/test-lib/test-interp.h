#ifndef CSPEAR_TEST_TEST_LIB_TEST_INTERP_H
#define CSPEAR_TEST_TEST_LIB_TEST_INTERP_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>

namespace {
  TEST(InterpTest,Interp) {
    csp::array<double> x = { // 5.25 and 5 are swapped
      0.  ,  0.25,  0.5 ,  0.75,  1.  ,  1.25,  1.5 ,  1.75,  2.  ,
      2.25,  2.5 ,  2.75,  3.  ,  3.25,  3.5 ,  3.75,  4.  ,  4.25,
      4.5 ,  4.75,  5.25,  5.  ,  5.5 ,  5.75,  6.  ,  6.25,  6.5 ,
      6.75,  7.  ,  7.25,  7.5 ,  7.75,  8.  ,  8.25,  8.5 ,  8.75,
      9.  ,  9.25,  9.5 ,  9.75, 10.
    };
    csp::array<double> xp = {
      0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0
    };
    csp::array<double> yp = {
      25.0, 16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0, 16.0, 25.0
    };
    auto y = csp::interp_sorted(x, xp, yp);

    std::vector<double> yres = {
      25.  , 22.75, 20.5 , 18.25, 16.  , 14.25, 12.5 , 10.75,  9.  ,
      7.75,  6.5 ,  5.25,  4.  ,  3.25,  2.5 ,  1.75,  1.  ,  0.75,
      0.5 ,  0.25,  0.25,  0.  ,  0.5 ,  0.75,  1.  ,  1.75,  2.5 ,
      3.25,  4.  ,  5.25,  6.5 ,  7.75,  9.  , 10.75, 12.5 , 14.25,
      16.  , 18.25, 20.5 , 22.75, 25.
    };
    EXPECT_EQ(yres.size(), y.size());
    for (int i = 0; i < y.size(); ++i) {
      EXPECT_DOUBLE_EQ(y[i], yres[i]);
    }

    // add some extrapolation
    csp::array<double> xp2 = {
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0
    };
    csp::array<double> yp2 = {
      16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0
    };
    auto y2 = csp::interp_sorted(x, xp2, yp2);
    std::vector<double> yres2 = {
      16. , 16.  , 16.  , 16.  , 16.  , 14.25, 12.5 , 10.75,  9.  ,
      7.75,  6.5 ,  5.25,  4.  ,  3.25,  2.5 ,  1.75,  1.  ,  0.75,
      0.5 ,  0.25,  0.25,  0.  ,  0.5 ,  0.75,  1.  ,  1.75,  2.5 ,
      3.25,  4.  ,  5.25,  6.5 ,  7.75,  9.  ,  9.  ,  9.  ,  9.  ,
      9.  ,  9.  ,  9.  ,  9.  ,  9.
    };
    EXPECT_EQ(yres2.size(), y2.size());
    for (int i = 0; i < y2.size(); ++i) {
      EXPECT_DOUBLE_EQ(y2[i], yres2[i]);
    }
  }
  TEST(InterpTest,InterpSorted) {
    csp::array<double> x = {
      0.  ,  0.25,  0.5 ,  0.75,  1.  ,  1.25,  1.5 ,  1.75,  2.  ,
      2.25,  2.5 ,  2.75,  3.  ,  3.25,  3.5 ,  3.75,  4.  ,  4.25,
      4.5 ,  4.75,  5.  ,  5.25,  5.5 ,  5.75,  6.  ,  6.25,  6.5 ,
      6.75,  7.  ,  7.25,  7.5 ,  7.75,  8.  ,  8.25,  8.5 ,  8.75,
      9.  ,  9.25,  9.5 ,  9.75, 10.
    };
    csp::array<double> xp = {
      0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0
    };
    csp::array<double> yp = {
      25.0, 16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0, 16.0, 25.0
    };
    auto y = csp::interp_sorted(x, xp, yp);

    std::vector<double> yres = {
      25.  , 22.75, 20.5 , 18.25, 16.  , 14.25, 12.5 , 10.75,  9.  ,
      7.75,  6.5 ,  5.25,  4.  ,  3.25,  2.5 ,  1.75,  1.  ,  0.75,
      0.5 ,  0.25,  0.  ,  0.25,  0.5 ,  0.75,  1.  ,  1.75,  2.5 ,
      3.25,  4.  ,  5.25,  6.5 ,  7.75,  9.  , 10.75, 12.5 , 14.25,
      16.  , 18.25, 20.5 , 22.75, 25.
    };
    EXPECT_EQ(yres.size(), y.size());
    for (int i = 0; i < y.size(); ++i) {
      EXPECT_DOUBLE_EQ(y[i], yres[i]);
    }

    // add some extrapolation
    csp::array<double> xp2 = {
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0
    };
    csp::array<double> yp2 = {
      16.0, 9.0, 4.0, 1.0, 0.0, 1.0, 4.0, 9.0
    };
    auto y2 = csp::interp_sorted(x, xp2, yp2);
    std::vector<double> yres2 = {
      16. , 16.  , 16.  , 16.  , 16.  , 14.25, 12.5 , 10.75,  9.  ,
      7.75,  6.5 ,  5.25,  4.  ,  3.25,  2.5 ,  1.75,  1.  ,  0.75,
      0.5 ,  0.25,  0.  ,  0.25,  0.5 ,  0.75,  1.  ,  1.75,  2.5 ,
      3.25,  4.  ,  5.25,  6.5 ,  7.75,  9.  ,  9.  ,  9.  ,  9.  ,
      9.  ,  9.  ,  9.  ,  9.  ,  9.
    };
    EXPECT_EQ(yres2.size(), y2.size());
    for (int i = 0; i < y2.size(); ++i) {
      EXPECT_DOUBLE_EQ(y2[i], yres2[i]);
    }
  }
}

#endif
