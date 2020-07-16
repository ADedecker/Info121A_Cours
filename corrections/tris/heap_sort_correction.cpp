#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

const int n = 63;

void print_as_tree(int* tab, size_t size, size_t root_index = 0) {
  static int space = -1;
  if(size <= root_index) return;
  space++;
  print_as_tree(tab, size, 2*root_index + 1);
  for (size_t i = 0; i < space; i++) {
    std::cout<<"\t";
  }
  std::cout<<tab[root_index]<<std::endl;
  print_as_tree(tab, size, 2*root_index + 2);
  space--;
}

void sift_down(int* tab, size_t size, size_t root_index = 0) {
  int val1, val2;
  if(size <= 2*root_index + 1) return;
  val1 = tab[2*root_index + 1];
  if(size <= 2*root_index + 2) val2 = val1;
  else val2 = tab[2*root_index + 2];
  if(tab[root_index] >= val1 && tab[root_index] >= val2) return;
  if(val1 < val2) { //Ne peut pas arriver si tab[2*root_index + 2] n'est pas défini
    std::swap(tab[root_index], tab[2*root_index + 2]);
    print_as_tree(tab, n);
    std::cout<<"============================================================================="<<std::endl;
    getchar();
    sift_down(tab, size, 2*root_index + 2);
  } else {
    std::swap(tab[root_index], tab[2*root_index + 1]);
    print_as_tree(tab, n);
    std::cout<<"============================================================================="<<std::endl;
    getchar();
    sift_down(tab, size, 2*root_index + 1);
  }
}

void make_heap(int* tab, size_t size, size_t root_index = 0) {
  if(size <= 2*root_index + 1) return;
  make_heap(tab, size, 2*root_index + 1);
  make_heap(tab, size, 2*root_index + 2);
  sift_down(tab, size, root_index);
}

void heap_sort(int* tab,  size_t size) {
  print_as_tree(tab, n);
  std::cout<<"============================================================================="<<std::endl;
  getchar();
  make_heap(tab, size);
  for (size_t i = size-1; i > 0 ; i--) {
    std::swap(tab[0], tab[i]);
    print_as_tree(tab, n);
    std::cout<<"============================================================================="<<std::endl;
    getchar();
    sift_down(tab, i);
  }
}

int main() {
  std::srand(std::time(nullptr));

  int* a = (int*)malloc(n*sizeof(int));
  if(a == nullptr) return 0;
  std::cout<<"Génération d'un tableau de "<<n<<" entiers..."<<std::endl;
  for (int i = 0; i < n; i++) {
    a[i] = std::rand()%n;
  }
  std::cout<<"Faites \"Enter\" pour lancer le tri"<<std::endl;
  getchar();
  heap_sort(a,n);
  std::cout<<"Tri effectué !"<<std::endl;
  free(a);
}
