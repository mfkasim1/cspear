#ifndef CSPEAR_LIB_INTERP_H
#define CSPEAR_LIB_INTERP_H

#include <algorithm>
#include <cspear/array/array.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/tools/assert.h>

namespace csp {
  /*
  */
  template <typename T, typename I>
  array<T,I> interp(
            const array<T,I>& x,
            const array<T,I>& xp,
            const array<T,I>& yp) {
    // sort the x first
    array<T,I> xc = x;
    std::sort(xc.data(), xc.data()+xc.size());

    // do the sorted interpolation
    return interp_sorted(xc, xp, yp);
  }

  template <typename T, typename I>
  array<T,I> interp_sorted(
            const array<T,I>& x,
            const array<T,I>& xp,
            const array<T,I>& yp) {

    // the arguments xp and yp must be 1D
    _cspear_assert((xp.ndim() == 1) && (yp.ndim() == 1),
      "interp and interp_sorted only works for 1 dimensional xp and yp");
    _cspear_assert(xp.size() == yp.size(),
      "The xp and yp must have the same length.");

    array<T,I> y = empty(x.shape());
    T left = yp[0];
    T right = yp[yp.size()-1];

    I ipl = 0; // pointer for xp and yp
    for (I ix = 0; ix < x.size(); ++ix) {
      auto& xi = x[ix];
      // move the p pointer until xi < xp[ipl+1]
      while (xi >= xp[ipl+1]) {
        ipl++;
        if (ipl == xp.size()-1) break;
      }

      // extrapolate on the right
      if (ipl == xp.size()-1) {
        for (I ix2 = ix; ix2 < x.size(); ++ix2) {
          y[ix2] = right;
        }
        break;
      }

      // get the interpolated elements
      auto& xpl = xp[ipl];
      auto& xpr = xp[ipl+1];

      // extrapolate on the left
      if (xi < xpl) {
        y[ix] = left;
      }
      // linearly interpolate
      else if (xi < xpr) {
        auto& ypl = yp[ipl];
        auto& ypr = yp[ipl+1];
        y[ix] = (ypr - ypl) * (xi - xpl) / (xpr - xpl) + ypl;
      }
    }
    return y;
  }
}

#endif
