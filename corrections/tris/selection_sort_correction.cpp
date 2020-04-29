#include <iostream>
#include <utility>

void selection_sort(int tab[], int taille) {
  for (int pos = 0; pos < taille-1; pos++) { //expliquer le -1
    int minpos = pos;
    for (int i = minpos+1; i < taille; i++) {
      if (tab[i]<tab[minpos]) minpos = i;
    }
    std::swap(tab[pos],tab[minpos]);
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  selection_sort(a,6);
  for (int i = 0; i < 6; i++) {
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  return 0;
}
