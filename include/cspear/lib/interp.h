#ifndef CSPEAR_LIB_INTERP_H
#define CSPEAR_LIB_INTERP_H

#include <algorithm>
#include <cspear/array/array.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/tools/assert.h>

namespace csp {
  template <typename XType, typename XPType, typename YPType,
            typename ResType=array<tools::Real,tools::Int,ContiguousView> >
  ResType interp_sorted(const XType& x, const XPType& xp, const YPType& yp) {
    using TX = typename XType::DataType;
    using IX = typename XType::IndexType;
    using ViewX = typename XType::ViewType;
    using TXP = typename XPType::DataType;
    using IXP = typename XPType::IndexType;
    using ViewXP = typename XPType::ViewType;
    using TYP = typename YPType::DataType;
    using IYP = typename YPType::IndexType;
    using ViewYP = typename YPType::ViewType;
    using TR = typename XType::DataType;
    using IR = typename XType::IndexType;
    using ViewR = typename XType::ViewType;

    // the arguments xp and yp must be 1D
    _cspear_assert((xp.ndim() == 1) && (yp.ndim() == 1),
      "interp and interp_sorted only works for 1 dimensional xp and yp");
    _cspear_assert(xp.size() == yp.size(),
      "The xp and yp must have the same length.");

    ResType y = ResType::empty(x.shape());
    TR left = (TR)yp[0];
    TR right = (TR)yp[yp.size()-1];

    IXP ipl = 0; // pointer for xp and yp
    // pointer for xp and yp
    auto ixpl = EWiseIterator<TXP,IXP,ViewXP>((TXP*)xp.data(), xp.view());
    auto ixpr = EWiseIterator<TXP,IXP,ViewXP>((TXP*)xp.data(), xp.view());
    auto iypl = EWiseIterator<TYP,IYP,ViewYP>((TYP*)yp.data(), yp.view());
    auto iypr = EWiseIterator<TYP,IYP,ViewYP>((TYP*)yp.data(), yp.view());
    ++ixpr; ++iypr;

    auto ix = EWiseIterator<TX,IX,ViewX>((TX*)x.data(), x.view());
    auto iy = EWiseIterator<TR,IR,ViewR>((TR*)y.data(), y.view());
    for (; ix; ++ix, ++iy) {
      auto& xi = *ix;

      // move the p pointer until xi < xp[ipl+1]
      while (xi >= *ixpr) {
        ++ixpl; ++ixpr;
        ++iypl; ++iypr;
        if (!ixpr) break;
      }

      // extrapolate on the right
      if (!ixpr) {
        for (; iy; ++iy) {
          *iy = right;
        }
        break;
      }

      // get the interpolated elements
      auto& xpl = *ixpl; // xp[ipl];
      auto& xpr = *ixpr; // xp[ipl+1];

      // extrapolate on the left
      if (xi < xpl) {
        *iy = left;
      }
      // linearly interpolate
      else if (xi < xpr) {
        auto& ypl = *iypl;
        auto& ypr = *iypr;
        *iy = (ypr - ypl) * (xi - xpl) / (xpr - xpl) + ypl;
      }
    }
    return y;
  }

  template <typename XType, typename XPType, typename YPType,
            typename ResType=array<tools::Real,tools::Int,ContiguousView> >
  ResType interp(const XType& x, const XPType& xp, const YPType& yp) {
    using TX = typename XType::DataType;
    using IX = typename XType::IndexType;
    using ViewX = typename XType::ViewType;

    // sort the x first
    array<TX,IX> xc = x;
    std::sort(xc.data(), xc.data()+xc.size());

    // do the sorted interpolation
    return interp_sorted<XType,XPType,YPType,ResType>(xc, xp, yp);
  }
}

#endif
