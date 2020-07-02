#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

/** Fonction int* partition(int* p_begin, int* p_end)
 *  Cette fonction choisit un pivot et partitionne selon ce pivot
 *  @param int* p_begin : l'adresse du premier élément du tableau à partitionner
 *  @param int* p_end : l'adresse juste après celle du dernier élément du tableau
 *  @return int* : l'adresse du pivot après partitionnement
 **/
int* partition(int* p_begin, int* p_end) {

}

/** Fonction void quick_sort(int* p_begin, int* p_end)
 *  Trie un tableau en utilisant l'algorithme quick_sort
 *  @param int* p_begin : l'adresse du premier élément du tableau à trier
 *  @param int* p_end : l'adresse juste après celle du dernier élément du tableau
 **/
void quick_sort(int* p_begin, int* p_end) {

}

/** Fonction void quick_sort(int* p_begin, int* p_end)
 *  Trie un tableau en utilisant l'algorithme quick_sort, avec optimisation de
 *  l'appel récursif terminal
 *  @param int* p_begin : l'adresse du premier élément du tableau à trier
 *  @param int* p_end : l'adresse juste après celle du dernier élément du tableau
 **/
void quicker_sort(int* p_begin, int* p_end) {

}

int main() {
  std::srand(std::time(nullptr));
  int n = 10;

  int* a = (int*)malloc(n*sizeof(int));
  if(a == nullptr) return 0;
  std::cout<<"Génération d'un tableau de "<<n<<" entiers..."<<std::endl;
  for (int i = 0; i < n; i++) {
    a[i] = std::rand()%n;
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  std::cout<<"Faites \"Enter\" pour lancer le tri"<<std::endl;
  getchar();
  quick_sort(a,a+n);
  std::cout<<"Tri effectué !"<<std::endl;
  for (int i = 0; i < n; i++) {
    std::cout<<a[i]<<";";
  }
  std::cout<<std::endl;
  free(a);
}
