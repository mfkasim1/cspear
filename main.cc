#ifndef MAIN_CC
#define MAIN_CC

#include <iostream>
#include <cspear/cspear>

int main() {
  // auto a = csp::array<double>({1,2,3});
  auto a = csp::arange<double>(10);
  a.reshape({2,5});
  a += 12;
  a.rdiv_(2);
  a = -a;

  for (int i = 0; i < a.size(); ++i) {
    std::cout << a.data()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "max: " << a.max() << std::endl;
  std::cout << "min: " << a.min() << std::endl;
  std::cout << "sum: " << a.sum() << std::endl;

  return 0;
}

#endif
