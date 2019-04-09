#ifndef CSPEAR_LIB_IO_H
#define CSPEAR_LIB_IO_H

#include <iostream>
#include <fstream>
#include <cspear/array/array.h>
#include <cspear/lib/print.h>

namespace csp {
  template <typename ArrType>
  void savetxt(const ArrType& arr, const char* fname) {
    std::ofstream file;
    file.open(fname);
    print_array(file, arr, " ", "\n", "", "");
    file << std::endl;
    file.close();
  }
}

#endif
