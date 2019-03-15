#ifndef CSPEAR_CORE_ASSERT_H
#define CSPEAR_CORE_ASSERT_H

#include <iostream>

namespace csp {
  void assert_cpu(void* ptr, const char* msg) {
    if (ptr == NULL) {
      std::cout << msg << std::endl;
    }
  }
}

#endif
