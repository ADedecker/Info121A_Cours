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
  int* p_i = (decltype(p_i))malloc(sizeof(*p_i));
  if(p_i == nullptr) return false;
  *p_i = 1;
  *p_resultat = 1;
  while(*p_i <= *p_n) {
    *p_resultat *= *p_i;
    (*p_i)++; //ATTENTION PARENTHÈSES
  }
  free(p_i);
  return true;
}

int main() {
  int* p_n = (decltype(p_n))malloc(sizeof(*p_n));
  int* p_resultat = (decltype(p_resultat))malloc(sizeof(*p_resultat));
  if(p_n != nullptr && p_resultat != nullptr) {
    *p_n = 10;
    std::cout<<"La version classique donne "<<fac_classique(*p_n);
    if(fac_pointeur(p_n,p_resultat)) {
      std::cout<<" et la version pointeurs donne "<<*p_resultat<<std::endl;
    } else {
      std::cout<<std::endl<<"Erreur d'allocation"<<std::endl;
    }
    free(p_resultat);
    free(p_n);
  } else {
    std::cout<<"Erreur d'allocation"<<std::endl;
  }
}
