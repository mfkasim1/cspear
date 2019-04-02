#ifndef CSPEAR_TEST_SIMD_TEST_AVX_H
#define CSPEAR_TEST_SIMD_TEST_AVX_H

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <cspear/simd/vector.h>
#include "test_params.h"

#ifdef __SIMD_AVX__

namespace {
  TEST(AVXTestDouble,Init1) {
    auto a = csp::simd::VectorAVX<double>(1.2);
    EXPECT_EQ(a.size(), 4);

    // store to a vector
    std::vector<double> vec(a.size());
    a.store(&vec[0]);
    for (int i = 0; i < vec.size(); ++i) {
      EXPECT_DOUBLE_EQ(vec[i], 1.2);
    }
  }
  TEST(AVXTestDouble,Init2) {
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
  TEST(AVXTestDouble,Init3) {
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
  TEST(AVXTestDouble,Load) {
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
  TEST(AVXTestDouble,PartialLoad1) {
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
  TEST(AVXTestDouble,PartialLoad2) {
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
  TEST(AVXTestDouble,PartialLoad3) {
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
  TEST(AVXTestDouble,PartialStore1) {
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
  TEST(AVXTestDouble,Neg) {
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    auto c = -b;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], -1.2);
    EXPECT_DOUBLE_EQ(vec[1], -2.4);
    EXPECT_DOUBLE_EQ(vec[2], -5.2);
    EXPECT_DOUBLE_EQ(vec[3], -6.5);
  }
  TEST(AVXTestDouble,Add) {
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
  TEST(AVXTestDouble,Sub) {
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
  TEST(AVXTestDouble,Mult) {
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
  TEST(AVXTestDouble,Div) {
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
  TEST(AVXTestDouble,AddInplace) {
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
  TEST(AVXTestDouble,SubInplace) {
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
  TEST(AVXTestDouble,MultInplace) {
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
  TEST(AVXTestDouble,DivInplace) {
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
  TEST(AVXTestDouble,AddAValue) {
    auto a = 1.2;
    auto b = csp::simd::VectorAVX<double>({1.2, 2.4, 5.2, 6.5});
    auto c = b + a;

    // store to a vector
    std::vector<double> vec(c.size());
    c.store(&vec[0]);
    EXPECT_DOUBLE_EQ(vec[0], 2.4);
    EXPECT_DOUBLE_EQ(vec[1], 3.6);
    EXPECT_DOUBLE_EQ(vec[2], 6.4);
    EXPECT_DOUBLE_EQ(vec[3], 7.7);
  }

  TEST(AVXTestFloat,Init1) {
    auto a = csp::simd::VectorAVX<float>(1.2);
    EXPECT_EQ(a.size(), 8);

    // store to a vector
    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    for (int i = 0; i < vec.size(); ++i) {
      EXPECT_FLOAT_EQ(vec[i], 1.2);
    }
  }
  TEST(AVXTestFloat,Init2) {
    auto a = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 1.2, 2.4, 5.2, 6.5});
    EXPECT_EQ(a.size(), 8);

    // store to a vector
    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 2.4);
    EXPECT_FLOAT_EQ(vec[2], 5.2);
    EXPECT_FLOAT_EQ(vec[3], 6.5);
    EXPECT_FLOAT_EQ(vec[4], 1.2);
    EXPECT_FLOAT_EQ(vec[5], 2.4);
    EXPECT_FLOAT_EQ(vec[6], 5.2);
    EXPECT_FLOAT_EQ(vec[7], 6.5);
  }
  TEST(AVXTestFloat,Init3) {
    try {
      auto a = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 1.3});
      FAIL() << "A runtime_error should be thrown with mismatch initializer.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown with mismatch initializer.";
    }
  }
  TEST(AVXTestFloat,Load) {
    std::vector<float> vec0 = {1.2, 2.4, 3.6, 4.8, 1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<float> a;
    a.load(&vec0[0]);

    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 2.4);
    EXPECT_FLOAT_EQ(vec[2], 3.6);
    EXPECT_FLOAT_EQ(vec[3], 4.8);
    EXPECT_FLOAT_EQ(vec[4], 1.2);
    EXPECT_FLOAT_EQ(vec[5], 2.4);
    EXPECT_FLOAT_EQ(vec[6], 3.6);
    EXPECT_FLOAT_EQ(vec[7], 4.8);
  }
  TEST(AVXTestFloat,PartialLoad1) {
    std::vector<float> vec0 = {1.2, 2.4, 3.6, 4.8, 1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<float> a;
    a.partial_load(&vec0[0], 7);
    EXPECT_EQ(a.size(), 8);

    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 2.4);
    EXPECT_FLOAT_EQ(vec[2], 3.6);
    EXPECT_FLOAT_EQ(vec[3], 4.8);
    EXPECT_FLOAT_EQ(vec[4], 1.2);
    EXPECT_FLOAT_EQ(vec[5], 2.4);
    EXPECT_FLOAT_EQ(vec[6], 3.6);
    EXPECT_FLOAT_EQ(vec[7], 0.0);
  }
  TEST(AVXTestFloat,PartialLoad2) {
    std::vector<float> vec0 = {1.2, 2.4, 3.6, 4.8, 1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<float> a;
    a.partial_load(&vec0[0], 4);
    EXPECT_EQ(a.size(), 8);

    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 2.4);
    EXPECT_FLOAT_EQ(vec[2], 3.6);
    EXPECT_FLOAT_EQ(vec[3], 4.8);
    EXPECT_FLOAT_EQ(vec[4], 0.0);
    EXPECT_FLOAT_EQ(vec[5], 0.0);
    EXPECT_FLOAT_EQ(vec[6], 0.0);
    EXPECT_FLOAT_EQ(vec[7], 0.0);
  }
  TEST(AVXTestFloat,PartialLoad3) {
    std::vector<float> vec0 = {1.2, 2.4, 3.6, 4.8, 1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<float> a;
    a.partial_load(&vec0[0], 1);
    EXPECT_EQ(a.size(), 8);

    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 0.0);
    EXPECT_FLOAT_EQ(vec[2], 0.0);
    EXPECT_FLOAT_EQ(vec[3], 0.0);
    EXPECT_FLOAT_EQ(vec[4], 0.0);
    EXPECT_FLOAT_EQ(vec[5], 0.0);
    EXPECT_FLOAT_EQ(vec[6], 0.0);
    EXPECT_FLOAT_EQ(vec[7], 0.0);
  }
  TEST(AVXTestFloat,PartialStore1) {
    std::vector<float> vec0 = {1.2, 2.4, 3.6, 4.8, 1.2, 2.4, 3.6, 4.8};
    csp::simd::VectorAVX<float> a;
    a.partial_load(&vec0[0], 1);
    EXPECT_EQ(a.size(), 8);

    std::vector<float> vec(a.size());
    a.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 1.2);
    EXPECT_FLOAT_EQ(vec[1], 0.0);
    EXPECT_FLOAT_EQ(vec[2], 0.0);
    EXPECT_FLOAT_EQ(vec[3], 0.0);
    EXPECT_FLOAT_EQ(vec[4], 0.0);
    EXPECT_FLOAT_EQ(vec[5], 0.0);
    EXPECT_FLOAT_EQ(vec[6], 0.0);
    EXPECT_FLOAT_EQ(vec[7], 0.0);
  }
  TEST(AVXTestFloat,Neg) {
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    auto c = -b;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], -1.2);
    EXPECT_FLOAT_EQ(vec[1], -2.4);
    EXPECT_FLOAT_EQ(vec[2], -5.2);
    EXPECT_FLOAT_EQ(vec[3], -6.5);
    EXPECT_FLOAT_EQ(vec[4], -2.2);
    EXPECT_FLOAT_EQ(vec[5], -3.4);
    EXPECT_FLOAT_EQ(vec[6], -6.2);
    EXPECT_FLOAT_EQ(vec[7], -7.5);
  }
  TEST(AVXTestFloat,Add) {
    auto a = csp::simd::VectorAVX<float>(1.2);
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    auto c = a + b;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 2.4);
    EXPECT_FLOAT_EQ(vec[1], 3.6);
    EXPECT_FLOAT_EQ(vec[2], 6.4);
    EXPECT_FLOAT_EQ(vec[3], 7.7);
    EXPECT_FLOAT_EQ(vec[4], 3.4);
    EXPECT_FLOAT_EQ(vec[5], 4.6);
    EXPECT_FLOAT_EQ(vec[6], 7.4);
    EXPECT_FLOAT_EQ(vec[7], 8.7);
  }
  TEST(AVXTestFloat,Sub) {
    auto a = csp::simd::VectorAVX<float>(1.2);
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    auto c = b - a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 0.0);
    EXPECT_FLOAT_EQ(vec[1], 1.2);
    EXPECT_FLOAT_EQ(vec[2], 4.0);
    EXPECT_FLOAT_EQ(vec[3], 5.3);
    EXPECT_FLOAT_EQ(vec[4], 1.0);
    EXPECT_FLOAT_EQ(vec[5], 2.2);
    EXPECT_FLOAT_EQ(vec[6], 5.0);
    EXPECT_FLOAT_EQ(vec[7], 6.3);
  }
  TEST(AVXTestFloat,Mult) {
    auto a = csp::simd::VectorAVX<float>(2.0);
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    auto c = b * a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 2.4);
    EXPECT_FLOAT_EQ(vec[1], 4.8);
    EXPECT_FLOAT_EQ(vec[2], 10.4);
    EXPECT_FLOAT_EQ(vec[3], 13.0);
    EXPECT_FLOAT_EQ(vec[4], 4.4);
    EXPECT_FLOAT_EQ(vec[5], 6.8);
    EXPECT_FLOAT_EQ(vec[6], 12.4);
    EXPECT_FLOAT_EQ(vec[7], 15.0);
  }
  TEST(AVXTestFloat,Div) {
    auto a = csp::simd::VectorAVX<float>(2.0);
    auto b = csp::simd::VectorAVX<float>({1.0, 2.0, 4.0, 6.0, 2.0, 4.0, 6.0, 8.0});
    auto c = b / a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 0.5);
    EXPECT_FLOAT_EQ(vec[1], 1.0);
    EXPECT_FLOAT_EQ(vec[2], 2.0);
    EXPECT_FLOAT_EQ(vec[3], 3.0);
    EXPECT_FLOAT_EQ(vec[4], 1.0);
    EXPECT_FLOAT_EQ(vec[5], 2.0);
    EXPECT_FLOAT_EQ(vec[6], 3.0);
    EXPECT_FLOAT_EQ(vec[7], 4.0);
  }
  TEST(AVXTestFloat,AddInplace) {
    auto c = csp::simd::VectorAVX<float>(1.2);
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    c += b;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 2.4);
    EXPECT_FLOAT_EQ(vec[1], 3.6);
    EXPECT_FLOAT_EQ(vec[2], 6.4);
    EXPECT_FLOAT_EQ(vec[3], 7.7);
    EXPECT_FLOAT_EQ(vec[4], 3.4);
    EXPECT_FLOAT_EQ(vec[5], 4.6);
    EXPECT_FLOAT_EQ(vec[6], 7.4);
    EXPECT_FLOAT_EQ(vec[7], 8.7);
  }
  TEST(AVXTestFloat,SubInplace) {
    auto a = csp::simd::VectorAVX<float>(1.2);
    auto c = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    c -= a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 0.0);
    EXPECT_FLOAT_EQ(vec[1], 1.2);
    EXPECT_FLOAT_EQ(vec[2], 4.0);
    EXPECT_FLOAT_EQ(vec[3], 5.3);
    EXPECT_FLOAT_EQ(vec[4], 1.0);
    EXPECT_FLOAT_EQ(vec[5], 2.2);
    EXPECT_FLOAT_EQ(vec[6], 5.0);
    EXPECT_FLOAT_EQ(vec[7], 6.3);
  }
  TEST(AVXTestFloat,MultInplace) {
    auto a = csp::simd::VectorAVX<float>(2.0);
    auto c = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    c *= a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 2.4);
    EXPECT_FLOAT_EQ(vec[1], 4.8);
    EXPECT_FLOAT_EQ(vec[2], 10.4);
    EXPECT_FLOAT_EQ(vec[3], 13.0);
    EXPECT_FLOAT_EQ(vec[4], 4.4);
    EXPECT_FLOAT_EQ(vec[5], 6.8);
    EXPECT_FLOAT_EQ(vec[6], 12.4);
    EXPECT_FLOAT_EQ(vec[7], 15.0);
  }
  TEST(AVXTestFloat,DivInplace) {
    auto a = csp::simd::VectorAVX<float>(2.0);
    auto c = csp::simd::VectorAVX<float>({1.0, 2.0, 4.0, 6.0, 2.0, 4.0, 6.0, 8.0});
    c /= a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 0.5);
    EXPECT_FLOAT_EQ(vec[1], 1.0);
    EXPECT_FLOAT_EQ(vec[2], 2.0);
    EXPECT_FLOAT_EQ(vec[3], 3.0);
    EXPECT_FLOAT_EQ(vec[4], 1.0);
    EXPECT_FLOAT_EQ(vec[5], 2.0);
    EXPECT_FLOAT_EQ(vec[6], 3.0);
    EXPECT_FLOAT_EQ(vec[7], 4.0);
  }
  TEST(AVXTestFloat,AddAValue) {
    auto a = 1.2;
    auto b = csp::simd::VectorAVX<float>({1.2, 2.4, 5.2, 6.5, 2.2, 3.4, 6.2, 7.5});
    auto c = b + a;

    // store to a vector
    std::vector<float> vec(c.size());
    c.store(&vec[0]);
    EXPECT_FLOAT_EQ(vec[0], 2.4);
    EXPECT_FLOAT_EQ(vec[1], 3.6);
    EXPECT_FLOAT_EQ(vec[2], 6.4);
    EXPECT_FLOAT_EQ(vec[3], 7.7);
    EXPECT_FLOAT_EQ(vec[4], 3.4);
    EXPECT_FLOAT_EQ(vec[5], 4.6);
    EXPECT_FLOAT_EQ(vec[6], 7.4);
    EXPECT_FLOAT_EQ(vec[7], 8.7);
    }
}

#endif

#endif
