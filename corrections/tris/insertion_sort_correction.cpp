#include <iostream>
#include <utility>

void insertion_sort_swap(int tab[], int taille) {
  for(int pos = 1; pos<taille; pos++) {
    int newpos = pos;
    while(newpos > 0 && tab[newpos-1]>tab[newpos]){
      std::swap(tab[newpos-1],tab[newpos]);
      newpos--;
    }
  }
}

void insertion_sort_shift(int tab[], int taille) {
  for(int pos = 1; pos<taille; pos++) {
    int val = tab[pos];
    int newpos = pos;
    while(newpos > 0 && tab[newpos-1]>val) {
      tab[newpos]=tab[newpos-1];
      newpos--;
    }
    tab[newpos] = val;
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  insertion_sort_shift(a,6);
  for (int i = 0; i < 6; i++) {
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  return 0;
}
