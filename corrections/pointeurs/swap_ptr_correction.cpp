#include <iostream>

template<typename T>
void swap_ref(T& a, T& b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template<typename T>
void swap_ptr(T* a, T* b) {
  T tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(int argc, char const *argv[]) {
  int a = 2, b = 3;
  std::cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  std::cout<<"swap_ref"<<std::endl;
  swap_ref(a,b);
  std::cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  std::cout<<"swap_ptr"<<std::endl;
  swap_ptr(&a,&b);
  std::cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  return 0;
}
