#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 15;

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
  if(root_index == 0) std::cout<<"============================================================================="<<std::endl;
}

void tamiser(int tab[], size_t size, size_t root_index = 0) {
  int val1, val2;
  if(size <= 2*root_index + 1) return;
  val1 = tab[2*root_index + 1];
  if(size <= 2*root_index + 2) val2 = val1;
  else val2 = tab[2*root_index + 2];
  if(tab[root_index] >= val1 && tab[root_index] >= val2) return;
  if(val1 < val2) {
    swap(tab[root_index], tab[2*root_index + 2]);
    print_as_tree(tab, size);
    getchar();
    tamiser(tab, size, 2*root_index + 2);
  } else {
    swap(tab[root_index], tab[2*root_index + 1]);
    print_as_tree(tab, size);
    getchar();
    tamiser(tab, size, 2*root_index + 1);
  }
}

void creerTas(int tab[], size_t size, size_t root_index = 0) {
  if(size <= 2*root_index + 1) return;
  creerTas(tab, size, 2*root_index + 1);
  creerTas(tab, size, 2*root_index + 2);
  tamiser(tab, size, root_index);
}

void heap_sort(int tab[],  size_t size) {
  print_as_tree(tab, size);
  getchar();
  creerTas(tab, size);
  for(int i = size-1; i > 0; i--) {
    swap(tab[0], tab[i]);
    print_as_tree(tab, i);
    getchar();
    tamiser(tab, i);
  }
}

int main() {
  std::srand(std::time(nullptr));

  int* a = (int*)malloc(n*sizeof(int));
  if(a == nullptr) return 0;
  std::cout<<"Génération d'un tableau de "<<n<<" entiers..."<<std::endl;
  for (int i = 0; i < n; i++) {
    a[i] = rand()%n;
    cout<<a[i]<<" ";
  }
  cout<<endl;
  std::cout<<"Faites \"Enter\" pour lancer le tri"<<std::endl;
  getchar();
  heap_sort(a,n);
  std::cout<<"Tri effectué !"<<std::endl;
  for (int i = 0; i < n; i++) {
    cout<<a[i]<<" ";
  }
  cout<<endl;
  free(a);
}
