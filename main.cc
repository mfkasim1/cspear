#ifndef MAIN_CC
#define MAIN_CC

#include <iostream>
#include <cspear/cspear>

int main() {
  // auto a = csp::array<double>({1,2,3});
  auto a = csp::arange<double>(10);

  for (int i = 0; i < a.size(); ++i) {
    std::cout << a.data()[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}

#endif
