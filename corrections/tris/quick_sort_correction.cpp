#include <iostream>
#include <utility>
#include <cstdlib>

int* partition(int* p_begin, int* p_end) {
  int* pivot = p_begin + (p_end-p_begin)/2; //Change to random
  std::swap(*pivot,*(p_end-1));
  pivot = p_end - 1;
  int* it1 = p_begin;
  for(int* it2 = p_begin; it2 != p_end-1; it2++) {
    if(*it2 <= *pivot) {
      std::swap(*it1, *it2);
      it1++;
    }
  }
  std::swap(*it1,*pivot);
  return it1;
}

void quicksort(int* p_begin, int* p_end) {
  if(p_end-p_begin <= 1) return;
  int* pivot = partition(p_begin, p_end);
  quicksort(p_begin,pivot);
  quicksort(pivot+1,p_end);
}

int main() {
  int* a = (int*)malloc(100*sizeof(int));
  for (int i = 0; i < 100; i++) {
    a[i] = (4269*i)%100;
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  quicksort(a,a+100);
  for (int i = 0; i < 100; i++) {
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  free(a);
}
