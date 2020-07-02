#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

int* partition(int* p_begin, int* p_end) {
  int* pivot = p_begin + std::rand()%(p_end-p_begin);
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

void quick_sort(int* p_begin, int* p_end) {
  if(p_end-p_begin <= 1) return;
  int* pivot = partition(p_begin, p_end);
  quick_sort(p_begin,pivot);
  quick_sort(pivot+1,p_end);
}

void quicker_sort(int* p_begin, int* p_end) {
  while(p_end-p_begin > 1) {
    int* pivot = partition(p_begin, p_end);
    quicker_sort(p_begin,pivot);
    p_begin = pivot+1;
  }
}

int main() {
  std::srand(std::time(nullptr));
  int n = 10000000;

  int* a = (int*)malloc(n*sizeof(int));
  if(a == nullptr) return 0;
  std::cout<<"Génération d'un tableau de "<<n<<" entiers..."<<std::endl;
  for (int i = 0; i < n; i++) {
    a[i] = std::rand()%n;
  }
  std::cout<<"Faites \"Enter\" pour lancer le tri"<<std::endl;
  getchar();
  quick_sort(a,a+n);
  std::cout<<"Tri effectué !"<<std::endl;
  free(a);
}
