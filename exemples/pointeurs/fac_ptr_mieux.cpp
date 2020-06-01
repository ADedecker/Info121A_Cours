#include <iostream>
#include <cstdlib>

using namespace std;

int fac_classique(int n) {
  //On fait exprès de décomposer toutes les opérations
  //pour faciliter le passage à la version "pointeur"
  int i = 1;
  int resultat = 1;
  while(i <= n) {
    resultat *= i;
    i++;
  }
  return resultat;
}

bool fac_pointeur(int* p_n, int* p_resultat) {
  int* p_i = (int*) malloc(sizeof(int));
  if(p_i == nullptr) return false;
  *p_i = 1;
  *p_resultat = 1;
  while(*p_i <= *p_n) {
    *p_resultat *= *p_i;
    (*p_i)++;
  }
  free(p_i);
  return true;
}

int main() {
  int* p_n = (int*) malloc(sizeof(int));
  int* p_resultat = (int*) malloc(sizeof(int));
  if(p_n == nullptr || p_resultat == nullptr) return 0;
  *p_n = 5;
  std::cout<<"La version classique donne "<<fac_classique(*p_n);
  if(!fac_pointeur(p_n,p_resultat)) {
    std::cout<<std::endl;
    return 0;
  }
  std::cout<<" et la version pointeurs donne "<<*p_resultat<<std::endl;
  //Libération de mémoire à faire
  free(p_n);
  free(p_resultat);
}
