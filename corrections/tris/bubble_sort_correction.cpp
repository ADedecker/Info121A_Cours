#include <iostream>
#include <utility>

void bubble_sort(int tab[], int taille) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = 0; i < taille-1; i++) {
      if (tab[i]>tab[i+1]) {
        std::swap(tab[i],tab[i+1]);
        sorted = false;
      }
    }
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  bubble_sort(a,6);
  for (int i = 0; i < 6; i++) {
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  return 0;
}
