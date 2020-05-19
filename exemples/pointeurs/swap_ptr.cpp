#include <iostream>

using namespace std;

template<typename T>
void swap_ref(T& a, T& b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template<typename T>
void swap_ptr(T* a, T* b) {
  //À compléter
}

int main(int argc, char const *argv[]) {
  int a = 2, b = 3;
  cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  cout<<"swap_ref"<<std::endl;
  swap_ref(a,b);
  cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  cout<<"swap_ptr"<<std::endl;
  swap_ptr(&a,&b);
  cout<<"a = "<<a<<"; b = "<<b<<";"<<std::endl;
  return 0;
}
