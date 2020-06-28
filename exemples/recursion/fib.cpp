#include <iostream>

template <int n>
constexpr unsigned long long static_fib = static_fib<n-1> + static_fib<n-2>;

template <>
constexpr unsigned long long static_fib<1> = 1;

template <>
constexpr unsigned long long static_fib<0> = 0;

unsigned long long fib(int n) {
  //Complexité exponentielle
  if(n==0) return 0;
  if(n==1) return 1;
  return fib(n-1) + fib(n-2);
}

unsigned long long fibiter(int n) {
  //Complexité linéaire
  unsigned long long a = 0;
  unsigned long long b = 1;
  if(n == 0) return 0;
  for (int i = 1; i < n; i++) {
    b=a+b;
    a=b-a;
  }
  return b;
}

unsigned long long fibutil(unsigned long long a, unsigned long long b, int n, int i) {
  if(i == n) return b;
  return fibutil(b,a+b,n,i+1);
}

unsigned long long fibcool(int n) {
  if(n == 0) return 0;
  return fibutil(0,1,n,1);
}

int main() {
  std::cout<<fibcool(100)<<std::endl;
}
