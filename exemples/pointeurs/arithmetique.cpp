#include <iostream>

using namespace std;

int main() {
  short a = 42;
  short* ptr = &a;
  cout<<(long)ptr<<" "<<(long)(ptr+1)<<" "<<(ptr+1)-ptr<<endl;
}
