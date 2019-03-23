#ifndef CSPEAR_TEST_MAIN_CC
#define CSPEAR_TEST_MAIN_CC

#include "gtest/gtest.h"
#include "array/test-init.h"
#include "array/test-reshape.h"
#include "array/test-reduce.h"
#include "array/test-op.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
