#ifndef CSPEAR_TEST_ARRAY_INIT_H
#define CSPEAR_TEST_ARRAY_INIT_H

#include <cstdlib>
#include <cspear/cspear>
#include "gtest/gtest.h"
#include "test_params.h"

namespace {
  template <typename T>
  class ArrayInitTest : public testing::Test {};

  using testing::Types;
  typedef Types<double, float> RealNumbers;
  TYPED_TEST_SUITE(ArrayInitTest, RealNumbers);

  TYPED_TEST(ArrayInitTest,InitializerList1D) {
    csp::array<TypeParam> arr = {4.5, 1.2, 3.2, 6.4};

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)4.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)1.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)3.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)6.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape.size(), 1);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,InitializerList2D) {
    csp::array<TypeParam> arr = {{4.5, 1.2, 3.2},
                              {6.4, 8.2, 7.1}};

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)4.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)1.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)3.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)6.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)8.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)7.1, AbsTol<TypeParam>::val);

    // check the shape
    std::vector<int> sh = {2,3};
    EXPECT_EQ(arr.shape(), sh);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,MemoryWithSize) {
    int sz = 5;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    csp::array<TypeParam> arr(a, sz);

    // free the memory
    std::free(a);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9.7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(shape.size(), 1);
  }

  TYPED_TEST(ArrayInitTest,MemoryWithShape) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<TypeParam> arr(a, {3,2});

    // free the memory
    std::free(a);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9.7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,CopyConstructor) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // doing the copy constructor
    csp::array<TypeParam> arr(arr1);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9.7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TYPED_TEST(ArrayInitTest,CopyOp) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<TypeParam> arr = {1.0, 2.1};

    // doing the copy operation
    arr = arr1.copy();
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9.7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TYPED_TEST(ArrayInitTest,AssignOp) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<TypeParam> arr = {1.0, 2.1};

    // doing the assignment operation
    arr = arr1;
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1.3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4.2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9.7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7.5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6.4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1.4, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TYPED_TEST(ArrayInitTest,EmptyInit) {
    csp::array<TypeParam> arr = csp::empty<TypeParam>({4,6});
    EXPECT_EQ(arr.size(), 24);

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,ZerosInit) {
    csp::array<TypeParam> arr = csp::zeros<TypeParam>({4,6});
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], 0);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,OnesInit) {
    csp::array<TypeParam> arr = csp::ones<TypeParam>({4,6});
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], 1);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,OnesInitIntFromAssignment) {
    csp::array<int> arr;
    arr = csp::ones<int>({4,6});
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], 1);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,FullInit) {
    csp::array<TypeParam> arr = csp::full<TypeParam>({4,6}, 5.0);
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], 5.0);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,FullInitFromAssignment) {
    csp::array<TypeParam> arr;
    arr = csp::full<TypeParam>({4,6}, 5.0);
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], 5.0);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit1) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(5.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)i);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit2) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(2.0, 7.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit3) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(2.0, 11.0, 3.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(3*i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit4) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(2.0, 12.0, 3.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(3*i+2));
    }

    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,LinspaceInit1) {
    csp::array<TypeParam> arr = csp::linspace<TypeParam>(2.0, 14.0, 4);

    // check the content
    EXPECT_EQ(arr[0], 2.0);
    EXPECT_EQ(arr[1], 6.0);
    EXPECT_EQ(arr[2], 10.0);
    EXPECT_EQ(arr[3], 14.0);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,RandomInit) {
    csp::array<TypeParam> arr = csp::random::random<TypeParam>({4,5});
    EXPECT_EQ(arr.size(), 20);
    EXPECT_EQ(arr.ndim(), 2);
    EXPECT_EQ(arr.shape()[0], 4);
    EXPECT_EQ(arr.shape()[1], 5);

    for (int i = 0; i < arr.size(); ++i) {
      EXPECT_TRUE(arr[i] < 1.0);
      EXPECT_TRUE(arr[i] >= 0.0);
    }
  }
}

#endif
