#ifndef CSPEAR_TEST_SIMD_TEST_AVX_H
#define CSPEAR_TEST_SIMD_TEST_AVX_H

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <cspear/simd/vector.h>

#ifdef __SIMD_AVX__

namespace {
  TEST(AVXTest,InitDouble1) {
    auto a = csp::simd::VectorAVX<double>(1.2);
    EXPECT_EQ(a.size(), 4);

    // store to a vector
    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    for (int i = 0; i < vec.size(); ++i) {
      EXPECT_DOUBLE_EQ(vec[i], 1.2);
    }
  }
  TEST(AVXTest,InitDouble2) {
    auto a = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    EXPECT_EQ(a.size(), 4);

    // store to a vector
    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 2.4);
    EXPECT_DOUBLE_EQ(vec[2], 5.2);
    EXPECT_DOUBLE_EQ(vec[3], 6.5);
  }
  TEST(AVXTest,InitDouble3) {
    try {
      auto a = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2});
      FAIL() << "A runtime_error should be thrown with mismatch initializer.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown with mismatch initializer.";
    }
  }
  TEST(AVXTest,Load) {
    std::vector<double> vec0 = {1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<double> a;
    a.load(&vec0[0]);

    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 2.4);
    EXPECT_DOUBLE_EQ(vec[2], 3.6);
    EXPECT_DOUBLE_EQ(vec[3], 4.8);
  }
  TEST(AVXTest,PartialLoad1) {
    std::vector<double> vec0 = {1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<double> a;
    a.partial_load(&vec0[0], 3);
    EXPECT_EQ(a.size(), 4);

    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 2.4);
    EXPECT_DOUBLE_EQ(vec[2], 3.6);
    EXPECT_DOUBLE_EQ(vec[3], 0.0);
  }
  TEST(AVXTest,PartialLoad2) {
    std::vector<double> vec0 = {1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<double> a;
    a.partial_load(&vec0[0], 2);
    EXPECT_EQ(a.size(), 4);

    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 2.4);
    EXPECT_DOUBLE_EQ(vec[2], 0.0);
    EXPECT_DOUBLE_EQ(vec[3], 0.0);
  }
  TEST(AVXTest,PartialLoad3) {
    std::vector<double> vec0 = {1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<double> a;
    a.partial_load(&vec0[0], 1);
    EXPECT_EQ(a.size(), 4);

    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 0.0);
    EXPECT_DOUBLE_EQ(vec[2], 0.0);
    EXPECT_DOUBLE_EQ(vec[3], 0.0);
  }
  TEST(AVXTest,PartialStore1) {
    std::vector<double> vec0 = {1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<double> a;
    a.partial_load(&vec0[0], 1);
    EXPECT_EQ(a.size(), 4);

    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 1.2);
    EXPECT_DOUBLE_EQ(vec[1], 0.0);
    EXPECT_DOUBLE_EQ(vec[2], 0.0);
    EXPECT_DOUBLE_EQ(vec[3], 0.0);
  }
  TEST(AVXTest,Add) {
    auto a = csp::simd::VectorAVX<double>(1.2);
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    auto c = a + b;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 2.4);
    EXPECT_DOUBLE_EQ(vec[1], 3.6);
    EXPECT_DOUBLE_EQ(vec[2], 6.4);
    EXPECT_DOUBLE_EQ(vec[3], 7.7);
  }
  TEST(AVXTest,Sub) {
    auto a = csp::simd::VectorAVX<double>(1.2);
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    auto c = b - a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 0.0);
    EXPECT_DOUBLE_EQ(vec[1], 1.2);
    EXPECT_DOUBLE_EQ(vec[2], 4.0);
    EXPECT_DOUBLE_EQ(vec[3], 5.3);
  }
  TEST(AVXTest,Mult) {
    auto a = csp::simd::VectorAVX<double>(2.0);
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    auto c = b * a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 2.4);
    EXPECT_DOUBLE_EQ(vec[1], 4.8);
    EXPECT_DOUBLE_EQ(vec[2], 10.4);
    EXPECT_DOUBLE_EQ(vec[3], 13.0);
  }
  TEST(AVXTest,Div) {
    auto a = csp::simd::VectorAVX<double>(2.0);
    auto b = csp::simd::VectorAVX<double>({1.0, 2.0, 4.0, 6.0});
    auto c = b / a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 0.5);
    EXPECT_DOUBLE_EQ(vec[1], 1.0);
    EXPECT_DOUBLE_EQ(vec[2], 2.0);
    EXPECT_DOUBLE_EQ(vec[3], 3.0);
  }
  TEST(AVXTest,AddInplace) {
    auto c = csp::simd::VectorAVX<double>(1.2);
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    c += b;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 2.4);
    EXPECT_DOUBLE_EQ(vec[1], 3.6);
    EXPECT_DOUBLE_EQ(vec[2], 6.4);
    EXPECT_DOUBLE_EQ(vec[3], 7.7);
  }
  TEST(AVXTest,SubInplace) {
    auto a = csp::simd::VectorAVX<double>(1.2);
    auto c = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    c -= a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 0.0);
    EXPECT_DOUBLE_EQ(vec[1], 1.2);
    EXPECT_DOUBLE_EQ(vec[2], 4.0);
    EXPECT_DOUBLE_EQ(vec[3], 5.3);
  }
  TEST(AVXTest,MultInplace) {
    auto a = csp::simd::VectorAVX<double>(2.0);
    auto c = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    c *= a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 2.4);
    EXPECT_DOUBLE_EQ(vec[1], 4.8);
    EXPECT_DOUBLE_EQ(vec[2], 10.4);
    EXPECT_DOUBLE_EQ(vec[3], 13.0);
  }
  TEST(AVXTest,DivInplace) {
    auto a = csp::simd::VectorAVX<double>(2.0);
    auto c = csp::simd::VectorAVX<double>({1.0, 2.0, 4.0, 6.0});
    c /= a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 0.5);
    EXPECT_DOUBLE_EQ(vec[1], 1.0);
    EXPECT_DOUBLE_EQ(vec[2], 2.0);
    EXPECT_DOUBLE_EQ(vec[3], 3.0);
  }
}

#endif

#endif
