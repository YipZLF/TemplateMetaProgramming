#include <iostream>

#include "meta.hpp"

template <class A>
using ReLU = if_else<op::greater<A, Number<0>>, A, Number<0>>;

int main() {
  using a = op::add<Number<4>, Number<6>>;
  using b = op::sub<Number<4>, Number<6>>;
  using c = op::mul<Number<4>, Number<6>>;
  using d = op::div<Number<4>, Number<6>>;

  print<a>();
  print<b>();
  print<c>();
  print<d>();

  using p_ab = pair<a, b>;
  print<p_ab>();

  using l = list<a, b, c, d>;
  print<l>();
  print<length<l>>();

  using flag = op::greater<b, a>;
  print<flag>();

  print<ReLU<a>>();
  print<ReLU<b>>();

  using mylist = Range<b, a>;
  print<mylist>();
  print<find<mylist, Number<2>>>();

  print<Sum<Number<1>, Number<100>>>();

  return 0;
}