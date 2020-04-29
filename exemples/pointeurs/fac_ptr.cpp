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

int* fac_pointeur(int* p_n) {
  //À compléter
}

int main() {
  int* n = //À compléter
  *n = 5
  std::cout<<"La version classique donne "<<fac_classique(*n);
  int* p_resultat = //À compléter
  std::cout<<" et la version pointeurs donne "<<*p_resultat<<std::endl;
  //Libération de mémoire à faire
}
