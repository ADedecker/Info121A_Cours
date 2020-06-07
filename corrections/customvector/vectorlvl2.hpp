#include <iostream>

template <typename T> // On fait un modèle de classe pour tout type T
struct Vector {
  T* debut = nullptr;
  T* fin = nullptr;
  T* finCap = nullptr;
  T& operator [](size_t i) { //Paramètre sous-entendu : VectorInt* this
    return (this->debut)[i];
  }
};

template <typename T>
void construireVector(Vector<T>* p_v, size_t taille, T val) {
  size_t capacite = taille ? taille : 1;
  p_v->debut = new T[taille];
  p_v->finCap = p_v->fin = p_v->debut+taille;
  for (size_t i = 0; i < taille; i++) {
    (p_v->debut)[i] = val;
  }
}

template <typename T>
void detruireVector(Vector<T>* p_v) {
  delete[] p_v->debut;
}

template <typename T>
size_t taille(Vector<T>* p_v) {
  return p_v->fin - p_v->debut;
}

template <typename T>
size_t capacite(Vector<T>* p_v) {
  return p_v->finCap - p_v->debut;
}

template <typename T>
void reserver(Vector<T>* p_v, size_t nouvelleCapacite) {
  if(nouvelleCapacite <= capacite(p_v)) return;
  T* nouveauDebut = new T[nouvelleCapacite];
  size_t _taille = taille(p_v);
  for (size_t i = 0; i < _taille; i++) {
    nouveauDebut[i] = (p_v->debut)[i];
  }
  delete[] p_v->debut;
  p_v->debut = nouveauDebut;
  p_v->fin = p_v->debut+_taille;
  p_v->finCap = p_v->debut+nouvelleCapacite;
}

template <typename T>
void changerTaille(Vector<T>* p_v, size_t nouvelleTaille, T val) {
  size_t ancienneTaille = taille(p_v);
  size_t ancienneCapacite = capacite(p_v);
  if(ancienneCapacite < nouvelleTaille) reserver(p_v,nouvelleTaille);
  p_v->fin = p_v->debut+nouvelleTaille;
  for (size_t i = ancienneTaille; i < nouvelleTaille; i++) {
    (p_v->debut)[i] = val;
  }
}

template <typename T>
void ajouterFin(Vector<T>* p_v, T val) {
  if(taille(p_v) == capacite(p_v)) {
    reserver(p_v,2*capacite(p_v));
  }
  *(p_v->fin++) = val;
}

template <typename T>
void enleverFin(Vector<T>* p_v) {
  p_v->fin--;
}
