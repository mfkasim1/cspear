#ifndef MAIN_CC
#define MAIN_CC

#include <iostream>
#include <initializer_list>
#include <cspear/cspear>

template <typename vec>
void p(const vec& v) {
  for (auto it = v.begin(); it < v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int test1() {
  // auto b = csp::array<double>({1,2,3});
  auto b = csp::arange(10000000.0);
  // a.reshape({2,5});
  // auto b = csp::random::randn<double>(a.shape());
  // a += 12;
  // a.rdiv_(2);
  // b.exp_();
  // // b = -a;
  //
  // p<std::vector<double> > ({1,2,3,4,5});
  auto c = -b;
  c.clip_lb_(-1);

  auto d = c / (b + 1);
  d += b;

  auto a = d;
  a[d > 1] += 10;

  for (int i = 0; i < 10; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;

  // for (int i = 0; i < b.size(); ++i) {
  //   std::cout << b.data()[i] << " ";
  // }
  // std::cout << std::endl;
  //
  // std::cout << "max: " << a.max() << std::endl;
  // std::cout << "min: " << a.min() << std::endl;
  // std::cout << "sum: " << a.sum() << std::endl;

  return 0;
}

int test_bcast() {
  auto a = csp::arange(10.0);
  auto b = csp::arange(10.0);
  auto c = a.expand_dims(0) + b.expand_dims(1);

  std::cout << "Shapes:" << std::endl;
  std::cout << a.shape()[0] << "," << a.shape()[1] << std::endl;
  std::cout << b.shape()[0] << "," << b.shape()[1] << std::endl;
  std::cout << c.shape()[0] << "," << c.shape()[1] << std::endl;
  std::cout << std::endl;

  std::cout << "Result:" << std::endl;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      std::cout << c[i*10+j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  return 0;
}

int main() {
  return test_bcast();
}

#endif
