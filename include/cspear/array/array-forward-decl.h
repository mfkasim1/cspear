#ifndef CSPEAR_ARRAY_ARRAY_FORWARD_DECLARATION_H
#define CSPEAR_ARRAY_ARRAY_FORWARD_DECLARATION_H

#include <cspear/tools/types.h>
#include <cspear/views/contiguous-view.h>

namespace csp {
  template <typename T, typename I=tools::Int,
            template<typename> typename View=ContiguousView>
  class array;
}

#endif
