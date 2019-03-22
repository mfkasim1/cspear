#ifndef CSPEAR_TEST_ARRAY_INIT_H
#define CSPEAR_TEST_ARRAY_INIT_H

#include <cstdlib>
#include <cspear/cspear>

namespace {
  TEST(InitArray,InitializerList1D) {
    csp::array<double> arr = {4.5, 1.2, 3.2, 6.4};

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 4.5);
    EXPECT_DOUBLE_EQ(arr[1], 1.2);
    EXPECT_DOUBLE_EQ(arr[2], 3.2);
    EXPECT_DOUBLE_EQ(arr[3], 6.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape.size(), 1);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TEST(InitArray,MemoryWithSize) {
    int sz = 5;
    double* a = (double*) std::malloc(sz * sizeof(double));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    csp::array<double> arr(a, sz);

    // free the memory
    std::free(a);

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 1.3);
    EXPECT_DOUBLE_EQ(arr[1], 4.2);
    EXPECT_DOUBLE_EQ(arr[2], 9.7);
    EXPECT_DOUBLE_EQ(arr[3], 7.5);
    EXPECT_DOUBLE_EQ(arr[4], 6.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(shape.size(), 1);
  }

  TEST(InitArray,MemoryWithShape) {
    int sz = 6;
    double* a = (double*) std::malloc(sz * sizeof(double));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<double> arr(a, {3,2});

    // free the memory
    std::free(a);

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 1.3);
    EXPECT_DOUBLE_EQ(arr[1], 4.2);
    EXPECT_DOUBLE_EQ(arr[2], 9.7);
    EXPECT_DOUBLE_EQ(arr[3], 7.5);
    EXPECT_DOUBLE_EQ(arr[4], 6.4);
    EXPECT_DOUBLE_EQ(arr[5], 1.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TEST(InitArray,CopyConstructor) {
    int sz = 6;
    double* a = (double*) std::malloc(sz * sizeof(double));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<double> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // doing the copy constructor
    csp::array<double> arr(arr1);

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 1.3);
    EXPECT_DOUBLE_EQ(arr[1], 4.2);
    EXPECT_DOUBLE_EQ(arr[2], 9.7);
    EXPECT_DOUBLE_EQ(arr[3], 7.5);
    EXPECT_DOUBLE_EQ(arr[4], 6.4);
    EXPECT_DOUBLE_EQ(arr[5], 1.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TEST(InitArray,CopyOp) {
    int sz = 6;
    double* a = (double*) std::malloc(sz * sizeof(double));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<double> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<double> arr = {1.0, 2.1};

    // doing the copy operation
    arr = arr1.copy();
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 1.3);
    EXPECT_DOUBLE_EQ(arr[1], 4.2);
    EXPECT_DOUBLE_EQ(arr[2], 9.7);
    EXPECT_DOUBLE_EQ(arr[3], 7.5);
    EXPECT_DOUBLE_EQ(arr[4], 6.4);
    EXPECT_DOUBLE_EQ(arr[5], 1.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TEST(InitArray,AssignOp) {
    int sz = 6;
    double* a = (double*) std::malloc(sz * sizeof(double));
    a[0] = 1.3;
    a[1] = 4.2;
    a[2] = 9.7;
    a[3] = 7.5;
    a[4] = 6.4;
    a[5] = 1.4;
    csp::array<double> arr1(a, {3,2});
    // free the memory
    std::free(a);

    // initialize arr with some arbitrary content
    csp::array<double> arr = {1.0, 2.1};

    // doing the assignment operation
    arr = arr1;
    // change one element in arr1 to make sure it makes a copy
    arr1[0] = 0;

    // check the content
    EXPECT_DOUBLE_EQ(arr[0], 1.3);
    EXPECT_DOUBLE_EQ(arr[1], 4.2);
    EXPECT_DOUBLE_EQ(arr[2], 9.7);
    EXPECT_DOUBLE_EQ(arr[3], 7.5);
    EXPECT_DOUBLE_EQ(arr[4], 6.4);
    EXPECT_DOUBLE_EQ(arr[5], 1.4);

    // check the shape
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TEST(InitArray,EmptyInit) {
    csp::array<double> arr = csp::empty({4,6});
    EXPECT_EQ(arr.size(), 24);

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 4);
    EXPECT_EQ(shape[1], 6);
    EXPECT_EQ(shape.size(), 2);
    EXPECT_EQ(arr.ndim(), 2);
  }

  TEST(InitArray,ZerosInit) {
    csp::array<double> arr = csp::zeros({4,6});
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

  TEST(InitArray,OnesInit) {
    csp::array<double> arr = csp::ones({4,6});
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

  TEST(InitArray,FullInit) {
    csp::array<double> arr = csp::full({4,6}, 5.0);
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

  TEST(InitArray,ArangeInit1) {
    csp::array<double> arr = csp::arange(5.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (double)i);
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TEST(InitArray,ArangeInit2) {
    csp::array<double> arr = csp::arange(2.0, 7.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (double)(i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(arr.ndim(), 1);
  }

  TEST(InitArray,ArangeInit3) {
    csp::array<double> arr = csp::arange(2.0, 11.0, 3.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (double)(3*i+2));
    }

    auto shape = arr.shape();
    EXPECT_EQ(arr.ndim(), 1);
  }

  TEST(InitArray,ArangeInit4) {
    csp::array<double> arr = csp::arange(2.0, 12.0, 3.0);

    // check the content
    for (auto i = 0; i < arr.size(); ++i) {
      EXPECT_EQ(arr[i], (double)(3*i+2));
    }

    EXPECT_EQ(arr.ndim(), 1);
  }

  TEST(InitArray,LinspaceInit1) {
    csp::array<double> arr = csp::linspace(2.0, 14.0, 4);

    // check the content
    EXPECT_EQ(arr[0], 2.0);
    EXPECT_EQ(arr[1], 6.0);
    EXPECT_EQ(arr[2], 10.0);
    EXPECT_EQ(arr[3], 14.0);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.ndim(), 1);
  }
}

#endif
