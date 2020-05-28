#include <cstdlib>
#include <iostream>

using namespace std;

struct Foo {
  int val = 42;
};

int main() {
  Foo* ptr = (decltype(ptr))malloc(sizeof(*ptr));
  std::cout<<ptr->val<<std::endl;
  free(ptr);
  return 0;
}
