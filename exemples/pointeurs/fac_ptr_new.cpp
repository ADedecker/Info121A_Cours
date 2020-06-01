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

void fac_pointeur(int* p_n, int* p_resultat) {
  int* p_i = new int(1);
  *p_resultat = 1;
  while(*p_i <= *p_n) {
    *p_resultat *= *p_i;
    (*p_i)++;
  }
  delete p_i;
}

int main() {
  try{
    int* p_n = new int(5);
    int* p_resultat = new int;
    std::cout<<"La version classique donne "<<fac_classique(*p_n);
    fac_pointeur(p_n,p_resultat);
    std::cout<<" et la version pointeurs donne "<<*p_resultat<<std::endl;
    delete p_n;
    delete p_resultat;
  } catch(...) {
    std::cout<<"Erreur d'allocation !"<<std::endl;
  }
}
