#ifndef CSPEAR_LIB_HIST_H
#define CSPEAR_LIB_HIST_H

#include <algorithm>
#include <cspear/array/array.h>
#include <cspear/tools/assert.h>
#include <cspear/tools/types.h>

namespace csp {
  template <typename TR=tools::Real, typename T=tools::Real,
            typename I=tools::Int>
  array<TR,I> hist(const array<T,I>& data, const array<T,I>& xbins) {
    // sort the data
    array<T,I> cdata = data;
    std::sort(cdata.data(), cdata.data()+cdata.size());

    return hist_sorted(cdata, xbins);
  }

  template <typename TR=tools::Real, typename T=tools::Real,
            typename I=tools::Int>
  array<TR,I> hist_sorted(const array<T,I>& data, const array<T,I>& xbins) {
    // xbins must be a 1D array
    _cspear_assert(xbins.ndim() == 1,
        "The second argument of hist must be a 1D array.");

    array<TR,I> res = zeros({xbins.size()-1});

    // data is already sorted

    I ibin = 0; // pointer for xbins
    for (I ix = 0; ix < data.size(); ++ix) {
      auto& xi = data[ix];
      // move the p pointer until xi < xbins[ibin+1]
      while (xi >= xbins[ibin+1]) {
        ibin++;
        if (ibin == xbins.size()-1) break;
      }

      // break if it's already out of the bins
      if (ibin == xbins.size()-1) {
        break;
      }

      // get the interpolated elements
      auto& xbinl = xbins[ibin];
      auto& xbinr = xbins[ibin+1];

      // increment the histogram
      if ((xi < xbinr) && (xbinl <= xi)) {
        res[ibin] += (TR)1;
      }
    }
    return res;
  }
}

#endif
