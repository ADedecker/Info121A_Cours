#include <cstdlib>
#include <iostream>

using namespace std;

struct Bar {
  int* ptr = nullptr;
};

void initBar(Bar* p_bar) {
  p_bar->ptr = (int*)malloc(sizeof(int));
}

void supprimeBar(Bar* p_bar) {
  free(p_bar->ptr);
}

int main() {
  Bar a, b;
  initBar(&a);
  initBar(&b);
  a = b;
  cout<<a.ptr<<" "<<b.ptr<<endl;
  supprimeBar(&a);
  supprimeBar(&b);
  return 0;
}
