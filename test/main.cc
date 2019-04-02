#ifndef CSPEAR_TEST_MAIN_CC
#define CSPEAR_TEST_MAIN_CC

#include "gtest/gtest.h"
#include "test_params.h"
#include "test-array/test-init.h"
#include "test-array/test-nil.h"
#include "test-array/test-reshape.h"
#include "test-array/test-reduce.h"
#include "test-array/test-op.h"
#include "test-array/test-bcast.h"
#include "test-view/test-filter-view.h"
#include "test-view/test-contiguous-view.h"
#include "test-lib/test-hist.h"
#include "test-lib/test-interp.h"
#include "test-simd/test-avx.h"
#include "test-cases/test-copy.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
