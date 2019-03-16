#ifndef CSPEAR_TOOLS_MISC_H
#define CSPEAR_TOOLS_MISC_H

#include <initializer_list>

namespace csp {
  namespace tools {
    template <typename T, typename Iterator>
    T _prod_init_list(Iterator begin, Iterator end) {
      T res = 1;
      for (auto it = begin; it < end; ++it) {
        res *= *it;
      }
      return res;
    }

    template <typename T>
    T _prod_init_list(const std::initializer_list<T>& a) {
      return _prod_init_list<T>(a.begin(), a.end());
    }
    template <typename T>
    T _prod_init_list(const std::vector<T>& a) {
      return _prod_init_list<T>(a.begin(), a.end());
    }
  }
}

#endif
