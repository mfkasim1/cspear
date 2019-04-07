#ifndef CSPEAR_TEST_ARRAY_INIT_H
#define CSPEAR_TEST_ARRAY_INIT_H

#include <cstdlib>
#include <cspear/cspear>
#include "gtest/gtest.h"
#include "test_params.h"

namespace {
  template <typename T>
  class ArrayInitTest : public testing::Test {};
  template <typename T>
  class ArrayInitRealTest : public testing::Test {};
  template <typename T>
  class ArrayInitOutlierTest : public testing::Test {};

  TYPED_TEST_SUITE(ArrayInitTest, AllNumbers);
  TYPED_TEST_SUITE(ArrayInitRealTest, RealNumbers);
  TYPED_TEST_SUITE(ArrayInitOutlierTest, RealDoubleNumber);

  TYPED_TEST(ArrayInitTest,InitializerList1D) {
    csp::array<TypeParam> arr = {(TypeParam)4, (TypeParam)1, (TypeParam)3, (TypeParam)6};

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)6, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape.size(), 1);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,InitializerList2D) {
    csp::array<TypeParam> arr = {{(TypeParam)4, (TypeParam)1, (TypeParam)3},
                                 {(TypeParam)6, (TypeParam)8, (TypeParam)7}};

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)7, AbsTol<TypeParam>::val);

    // check the shape
    std::vector<int> sh = {2,3};
    EXPECT_EQ(arr.shape(), sh);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,MemoryWithSize) {
    int sz = 5;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = (TypeParam)1;
    a[1] = (TypeParam)4;
    a[2] = (TypeParam)9;
    a[3] = (TypeParam)7;
    a[4] = (TypeParam)6;
    csp::array<TypeParam> arr(a, sz);

    // free the memory
    std::free(a);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(shape.size(), 1);
  }

  TYPED_TEST(ArrayInitTest,MemoryWithShape) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = (TypeParam)1;
    a[1] = (TypeParam)4;
    a[2] = (TypeParam)9;
    a[3] = (TypeParam)7;
    a[4] = (TypeParam)6;
    a[5] = (TypeParam)1;
    csp::array<TypeParam> arr(a, {3,2});

    // free the memory
    std::free(a);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1, AbsTol<TypeParam>::val);

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
    a[0] = (TypeParam)1;
    a[1] = (TypeParam)4;
    a[2] = (TypeParam)9;
    a[3] = (TypeParam)7;
    a[4] = (TypeParam)6;
    a[5] = (TypeParam)1;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // doing the copy constructor
    csp::array<TypeParam> arr(arr1);

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TYPED_TEST(ArrayInitTest,CopyOp) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = (TypeParam)1;
    a[1] = (TypeParam)4;
    a[2] = (TypeParam)9;
    a[3] = (TypeParam)7;
    a[4] = (TypeParam)6;
    a[5] = (TypeParam)1;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<TypeParam> arr = {(TypeParam)1, (TypeParam)2};

    // doing the copy operation
    arr = arr1.copy();
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1, AbsTol<TypeParam>::val);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TYPED_TEST(ArrayInitTest,AssignOp) {
    int sz = 6;
    TypeParam* a = (TypeParam*) std::malloc(sz * sizeof(TypeParam));
    a[0] = 1;
    a[1] = 4;
    a[2] = 9;
    a[3] = 7;
    a[4] = 6;
    a[5] = 1;
    csp::array<TypeParam> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<TypeParam> arr = {(TypeParam)1, (TypeParam)2};

    // doing the assignment operation
    arr = arr1;
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_NEAR(arr[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(arr[5], (TypeParam)1, AbsTol<TypeParam>::val);

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
      EXPECT_EQ(arr[i], (TypeParam)1);
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
      EXPECT_EQ(arr[i], (TypeParam)1);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,FullInit) {
    csp::array<TypeParam> arr = csp::full<TypeParam>({4,6}, (TypeParam)5);
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)5);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,FullInitFromAssignment) {
    csp::array<TypeParam> arr;
    arr = csp::full<TypeParam>({4,6}, (TypeParam)5);
    EXPECT_EQ(arr.size(), 24);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)5);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit1) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>((TypeParam)5);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)i);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit2) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>((TypeParam)2, (TypeParam)7);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit3) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(
        (TypeParam)2,
        (TypeParam)11,
        (TypeParam)3);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(3*i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,ArangeInit4) {
    csp::array<TypeParam> arr = csp::arange<TypeParam>(
        (TypeParam)2,
        (TypeParam)12,
        (TypeParam)3);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (TypeParam)(3*i+2));
    }

    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitTest,LinspaceInit1) {
    csp::array<TypeParam> arr = csp::linspace<TypeParam>(
        (TypeParam)2, (TypeParam)14, 4);

    // check the content
    EXPECT_EQ(arr[0], (TypeParam)2);
    EXPECT_EQ(arr[1], (TypeParam)6);
    EXPECT_EQ(arr[2], (TypeParam)10);
    EXPECT_EQ(arr[3], (TypeParam)14);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitRealTest,LinspaceInit2) {
    csp::array<TypeParam> arr = csp::linspace<TypeParam>(
        (TypeParam)0, (TypeParam)1, 3);

    // check the content
    EXPECT_EQ(arr[0], (TypeParam)0);
    EXPECT_EQ(arr[1], (TypeParam)0.5);
    EXPECT_EQ(arr[2], (TypeParam)1);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TYPED_TEST(ArrayInitRealTest,RandomInit) {
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

  TYPED_TEST(ArrayInitOutlierTest,ZeroSizeArray) {
    csp::array<TypeParam> a = csp::empty<TypeParam>({});
    EXPECT_EQ(a.size(), 0);
    csp::array<TypeParam> b = csp::empty<TypeParam>({1,0});
    EXPECT_EQ(b.size(), 0);
    csp::array<TypeParam> c = csp::zeros<TypeParam>({});
    EXPECT_EQ(c.size(), 0);
    csp::array<TypeParam> d = csp::ones<TypeParam>({});
    EXPECT_EQ(d.size(), 0);
    csp::array<TypeParam> e = csp::arange<TypeParam>((TypeParam)-8);
    EXPECT_EQ(e.size(), 0);
    csp::array<TypeParam> f = csp::linspace<TypeParam>(
                                  (TypeParam)3, (TypeParam)1, 0);
    EXPECT_EQ(f.size(), 0);
  }
}

#endif
