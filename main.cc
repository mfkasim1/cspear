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

int main() {
  // auto b = csp::array<double>({1,2,3});
  auto b = csp::arange(10.0);
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
  a[d > 1] += 1;

  for (int i = 0; i < a.size(); ++i) {
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

#endif
