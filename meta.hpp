#include <iostream>

namespace type_tag {

#define BOOLEAN 0
#define NONE 1
#define NUMBER 2
#define PAIR 3
#define LIST 4

template <uint32_t Index>
struct type {
  static const uint32_t tag = Index;
};

using boolean_type = type<BOOLEAN>;
using number_type = type<NUMBER>;
using none_type = type<NONE>;
using pair_type = type<PAIR>;
using list_type = type<LIST>;
}  // namespace type_tag

template <bool Flag>
struct Boolean {
  static const bool flag = Flag;
  using type = type_tag::boolean_type;
};

using True = Boolean<true>;
using False = Boolean<false>;

template <int64_t Numerator, int64_t Denominator = 1>
struct Number {
  static const int numer = Numerator;
  static const int denom = Denominator;
  using type = type_tag::number_type;
};

namespace op {
template <class A, class B>
using add =
    Number<A::numer * B::denom + A::denom * B::numer, A ::denom * B::denom>;

template <class A, class B>
using sub =
    Number<A::numer * B::denom - A::denom * B::numer, A ::denom * B::denom>;

template <class A, class B>
using mul = Number<A::numer * B::numer, A ::denom * B::denom>;

template <class A, class B>
using div = Number<A::numer * B::denom, A ::denom * B::numer>;

template <class A, class B>
using greater = Boolean<(A::numer * B::denom - A::denom * B::numer > 0)>;

template <class A, class B>
using greater_or_eq = Boolean<(A::numer * B::denom - A::denom * B::numer >= 0)>;

template <class A, class B>
using less = Boolean<(A::numer * B::denom - A::denom * B::numer < 0)>;

template <class A, class B>
using less_or_eq = Boolean<(A::numer * B::denom - A::denom * B::numer <= 0)>;

template <class A>
using isNone = Boolean<A::type::tag == NONE>;

template <class A>
using Not = Boolean<!A::flag>;

template <class A, class B>
using And = Boolean<A::flag && B::flag>;

template <class A, class B>
using Or = Boolean<A::flag || B::flag>;

}  // namespace op

struct None {
  using type = type_tag::none_type;
};

template <class First, class Second>
struct pair {
  using first = First;
  using second = Second;
  using type = type_tag::pair_type;
};

template <class... T>
struct list {
  using type = type_tag::list_type;
};

template <class T>
struct list<T> : public pair<T, None> {};

template <class First, class... T>
struct list<First, T...> : public pair<First, list<T...>> {};

template <class Flag, class ifTrue, class ifFalse>
struct if_else_ : public ifTrue {};

template <class ifTrue, class ifFalse>
struct if_else_<False, ifTrue, ifFalse> : public ifFalse {};

template <class Flag, class ifTrue, class ifFalse>
struct if_else : public if_else_<Flag, ifTrue, ifFalse> {};

template <class T>
struct length;

template <>
struct length<None> : public Number<0> {};

template <class List>
struct length
    : public if_else<op::Not<op::isNone<typename List::second>>,
                     op::add<Number<1>, length<typename List::second>>,
                     Number<1>> {};

template <class List, class Index>
struct find
    : public if_else<op::greater<Index, Number<0>>,
                     find<typename List::second, op::sub<Index, Number<1>>>,
                     typename List::first> {};

template <class StartNumber, class EndNumber, class Step = Number<1>>
struct Range
    : public if_else<
          op::less<StartNumber, EndNumber>,
          pair<StartNumber, Range<op::add<StartNumber, Step>, EndNumber, Step>>,
          None> {};

template <class StartNumber, class EndNumber, class Step = Number<1>,
          class Result = Number<0>>
struct Sum : public if_else<op::less_or_eq<StartNumber, EndNumber>,
                            Sum<op::add<StartNumber, Step>, EndNumber, Step,
                                op::add<StartNumber, Result>>,
                            Result> {};

/* Print */
template <class T>
struct print_impl {
  static void print(type_tag::number_type) {
    if (T::denom == 1) {
      std::cout << T::numer;
    } else {
      std::cout << T::numer << '/' << T::denom;
    }
  }

  static void print(type_tag::pair_type) {
    print_impl<typename T::first>::print(typename T::first::type());
    std::cout << ", ";
    print_impl<typename T::second>::print(typename T::second::type());
  }
  static void print(type_tag::list_type) {
    print_impl<typename T::first>::print(typename T::first::type());
    std::cout << ", ";
    print_impl<typename T::second>::print(typename T::second::type());
  }

  static void print(type_tag ::boolean_type) {
    if (T ::flag) {
      std::cout << "True";
    } else {
      std::cout << "False";
    }
  }

  static void print(type_tag ::none_type) { return; }
};

template <class T>
void print() {
  print_impl<T>::print(typename T::type());
  std::cout << std::endl;
}
