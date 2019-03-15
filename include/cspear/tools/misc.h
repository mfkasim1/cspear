#ifndef CSPEAR_TOOLS_MISC_H
#define CSPEAR_TOOLS_MISC_H

#include <initializer_list>

namespace csp {
  namespace tools {
    template <typename T>
    T _prod_init_list(const std::initializer_list<T>& a) {
      T res = 1;
      for (auto it = a.begin(); it < a.end(); ++it) {
        res *= *it;
      }
      return res;
    }
  }
}

#endif
