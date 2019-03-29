#ifndef CSPEAR_TOOLS_TIME_H
#define CSPEAR_TOOLS_TIME_H

#include <chrono>

namespace csp {
  namespace tools {

    class time {
      std::chrono::high_resolution_clock::time_point t_;
      public:
      time(std::chrono::high_resolution_clock::time_point t) {
        t_ = t;
      }

      double tonow() {
        std::chrono::high_resolution_clock::time_point now =
          std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration =
          std::chrono::duration_cast< std::chrono::duration<double> >(now-t_);
        return duration.count();
      }

      static time now() {
        time r(std::chrono::high_resolution_clock::now());
        return r;
      }
    };
  }
}

#endif
