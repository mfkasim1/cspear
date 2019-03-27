#ifndef CSPEAR_ARRAY_UFUNCS_H
#define CSPEAR_ARRAY_UFUNCS_H

namespace csp {
  namespace ufunc {
    // unary operations
    template <typename T>
    struct neg {
      static inline T unary(const T& a) { return -a; }
    };
    template <typename T>
    struct logical_not {
      static inline bool unary(const T& a) { return !a; }
    };

    // binary operations
    template <typename T>
    struct add {
      static inline T binary(const T& a, const T& b) { return a + b; }
    };
    template <typename T>
    struct sub {
      static inline T binary(const T& a, const T& b) { return a - b; }
    };
    template <typename T>
    struct mult {
      static inline T binary(const T& a, const T& b) { return a * b; }
    };
    template <typename T>
    struct div {
      static inline T binary(const T& a, const T& b) { return a / b; }
    };
    template <typename T>
    struct reciprocal {
      static inline T binary(const T& a, const T& b) { return b / a; }
    };
    template <typename T>
    struct assign {
      static inline T binary(const T& a, const T& b) { return b; }
    };
    template <typename T>
    struct clip_lb {
      static inline T binary(const T& a, const T& lb) { return a < lb ? lb : a; }
    };
    template <typename T>
    struct clip_ub {
      static inline T binary(const T& a, const T& ub) { return a > ub ? ub : a; }
    };
    template <typename T>
    struct gt {
      static inline bool binary(const T& a, const T& b) { return a > b; }
    };
    template <typename T>
    struct lt {
      static inline bool binary(const T& a, const T& b) { return a < b; }
    };
    template <typename T>
    struct gteq {
      static inline bool binary(const T& a, const T& b) { return a >= b; }
    };
    template <typename T>
    struct lteq {
      static inline bool binary(const T& a, const T& b) { return a <= b; }
    };
    template <typename T>
    struct eq {
      static inline bool binary(const T& a, const T& b) { return a == b; }
    };
    template <typename T>
    struct neq {
      static inline bool binary(const T& a, const T& b) { return a != b; }
    };
    template <typename T>
    struct logical_and {
      static inline bool binary(const T& a, const T& b) { return a && b; }
    };
    template <typename T>
    struct logical_or {
      static inline bool binary(const T& a, const T& b) { return a || b; }
    };

    // ternary operations
    template <typename T>
    struct clip {
      static inline T ternary(const T& a, const T& lb, const T& ub) {
        return (a < lb) ? lb : ((a > ub) ? ub : a);
      }
    };
  }
}

#endif
