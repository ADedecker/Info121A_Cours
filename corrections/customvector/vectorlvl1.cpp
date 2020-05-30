#include <iostream>

#include "vectorlvl1.hpp"

using namespace std;

bool initVectorInt(VectorInt* p_v, size_t taille, int val) {
  p_v->debut = (int*)malloc(taille * sizeof(int));
  if (p_v->debut == nullptr) return false;
  p_v->fin = p_v->debut+taille;
  for (size_t i = 0; i < taille; i++) {
    (p_v->debut)[i] = val;
  }
  return true;
}

void supprimerVectorInt(VectorInt* p_v) {
  free(p_v->debut);
}

size_t taille(VectorInt* p_v) {
  return p_v->fin - p_v->debut;
}

int lire(VectorInt* p_v, size_t i) {
  return (p_v->debut)[i];
}

void ecrire(VectorInt* p_v, size_t i, int val) {
  (p_v->debut)[i] = val;
}

bool changeTaille(VectorInt* p_v, size_t nouvelleTaille, int val) {
  int* ancienDebut = p_v->debut;
  size_t ancienneTaille = taille(p_v);
  p_v->debut = (int*)realloc(p_v->debut, nouvelleTaille * sizeof(int));
  if (p_v->debut == nullptr) {
    p_v->debut = ancienDebut;
    return false;
  }
  p_v->fin = p_v->debut + nouvelleTaille;
  for (size_t i = ancienneTaille; i < nouvelleTaille; i++) {
    (p_v->debut)[i] = val;
  }
  return true;
}

bool ajouteFin(VectorInt* p_v, int val) {
  return changeTaille(p_v,taille(p_v)+1,val);
}

int main() {
  VectorInt v;
  if(initVectorInt(&v,10,1)) {
    cout<<taille(&v)<<endl;
    cout<<lire(&v,9)<<endl;
    if(ajouteFin(&v,2)) {
      cout<<taille(&v)<<endl;
      cout<<lire(&v,9)<<endl;
      cout<<lire(&v,10)<<endl;
    }
    if(changeTaille(&v, 1ul<<16, 42)){
      cout<<taille(&v)<<endl;
      cout<<lire(&v,9)<<endl;
      cout<<lire(&v,10)<<endl;
      cout<<lire(&v,11)<<endl;
    }
    supprimerVectorInt(&v); //Démo en supprimant + getchar
  }
  return 0;
}
