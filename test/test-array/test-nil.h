#ifndef CSPEAR_TEST_TEST_ARRAY_TEST_NIL_H
#define CSPEAR_TEST_TEST_ARRAY_TEST_NIL_H

#include <cstdint>
#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class EmptyArrayTest : public testing::Test {};

  TYPED_TEST_SUITE(EmptyArrayTest, AllTypes);

  TYPED_TEST(EmptyArrayTest, Init1) {
    csp::array<TypeParam> arr = {};

    std::vector<int> shape = {};
    EXPECT_EQ(arr.ndim(), 0);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.shape(), shape);
  }
  TYPED_TEST(EmptyArrayTest, Op) {
    csp::array<TypeParam> a = {};
    csp::array<TypeParam> arr = {};
    try {
      auto b = a == arr;
      FAIL() << "A runtime_error should be thrown for operating with "
                "empty array";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for operating with "
                "empty array";
    }
  }
  TYPED_TEST(EmptyArrayTest, BCast) {
    csp::array<TypeParam> a = {1, 0};
    csp::array<TypeParam> arr = {};
    try {
      auto b = a == arr;
      FAIL() << "A runtime_error should be thrown for broadcasting with "
                "empty array";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for broadcasting with "
                "empty array";
    }
  }
  TYPED_TEST(EmptyArrayTest, Reduce) {
    csp::array<TypeParam> arr = {};
    try {
      auto b = arr.all();
      FAIL() << "A runtime_error should be thrown for reduce with "
                "empty array";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for reduce with "
                "empty array";
    }
  }
}

#endif
