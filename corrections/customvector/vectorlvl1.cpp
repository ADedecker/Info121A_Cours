#include <iostream>

#include "vectorlvl1.hpp"

using namespace std;

bool construireVectorInt(VectorInt* p_v, size_t taille, int val) {
  p_v->debut = (int*)malloc(taille * sizeof(int));
  if (p_v->debut == nullptr) return false;
  p_v->fin = p_v->debut+taille;
  for (size_t i = 0; i < taille; i++) {
    (p_v->debut)[i] = val;
  }
  return true;
}

void detruireVectorInt(VectorInt* p_v) {
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

bool changerTaille(VectorInt* p_v, size_t nouvelleTaille, int val) {
  size_t ancienneTaille = taille(p_v);
  int* nouveauDebut = (int*)realloc(p_v->debut, nouvelleTaille * sizeof(int));
  if (nouveauDebut == nullptr) return false;
  p_v->debut = nouveauDebut;
  p_v->fin = p_v->debut + nouvelleTaille;
  for (size_t i = ancienneTaille; i < nouvelleTaille; i++) {
    (p_v->debut)[i] = val;
  }
  return true;
}

bool ajouterFin(VectorInt* p_v, int val) {
  return changerTaille(p_v,taille(p_v)+1,val);
}

int main() {
  VectorInt v;
  if(construireVectorInt(&v,10,1)) {
    cout<<taille(&v)<<endl;
    cout<<lire(&v,9)<<endl;
    if(ajouterFin(&v,2)) {
      cout<<taille(&v)<<endl;
      cout<<lire(&v,9)<<endl;
      cout<<lire(&v,10)<<endl;
    }
    if(changerTaille(&v, 1ul<<16, 42)){
      cout<<taille(&v)<<endl;
      cout<<lire(&v,9)<<endl;
      cout<<lire(&v,10)<<endl;
      cout<<lire(&v,11)<<endl;
    }
    detruireVectorInt(&v); //Démo en supprimant + getchar
  }
  return 0;
}
