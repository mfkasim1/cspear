#ifndef CSPEAR_TOOLS_ASSERT_H
#define CSPEAR_TOOLS_ASSERT_H

#include <iostream>
#define _cspear_assert(i,c) if(!(i)) throw std::runtime_error(c);

namespace csp {
  namespace tools {
    void _assert_cpu(void* ptr, const char* msg) {
      if (ptr == NULL) {
        std::cout << msg << std::endl;
      }
    }
  }
}

#endif
