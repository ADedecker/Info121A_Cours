#include <iostream>

using namespace std;

void swap_ref(int& a, int& b) {
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}

void swap_ptr(int* p_a, int* p_b) {
  int tmp;
  tmp = *p_a;
  *p_a = *p_b;
  *p_b = tmp;
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
