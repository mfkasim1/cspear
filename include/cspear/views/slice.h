#ifndef CSPEAR_VIEWS_SLICE_H
#define CSPEAR_VIEWS_SLICE_H

#include <initializer_list>
#include <stdexcept>
#include <cspear/tools/types.h>

namespace csp {
  template <typename I>
  struct Slice {
    I begin; // inclusion
    I end; // exclusion
    I step;
    I nelmt;

    Slice (I v) {
      begin = v;
      end = v + 1;
      step = 1;
    }
    Slice(std::initializer_list<I> r) {
      auto sz = r.size();
      auto it = r.begin();
      switch (sz) {
        case 1: {
          auto v = it[0];
          begin = v;
          end = v + 1;
          step = 1;
          break;
        }
        case 2: {
          begin = it[0];
          end = it[1];
          step = 1;
          break;
        }
        case 3: {
          begin = it[0];
          end = it[1];
          step = it[2];
          break;
        }
        default: {
          throw std::runtime_error("Slice needs to have 1 to 3 elements");
        }
      }
    }
    template <typename I2>
    Slice(const Slice<I2>& s) {
      begin = (I)s.begin;
      end = (I)s.end;
      step = (I)s.step;
      nelmt = (I)s.nelmt;
    }

    void normalize(I sz) {
      end = end > sz ? sz : end;
      if (step > 1) {
        end = ((end-begin-1) / step) * step + begin + 1;
      }
      else if (step == 0) {
        end = sz;
        step = 1;
      }
      // recalculate the number of elements
      nelmt = (end - begin) / step;
      if ((end - begin) != step * nelmt)
        ++nelmt;
      nelmt = (nelmt < 0) ? 0 : nelmt;
    }
  };

  template <typename I=tools::Int>
  Slice<I> whole() {
    return Slice<I>({0,0,0});
  }
}

#endif
