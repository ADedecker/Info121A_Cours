#include <iostream>

template <typename T> // On fait un modèle de classe pour tout type T
struct Vector {
  T* debut = nullptr;
  T* fin = nullptr;
  T* finCap = nullptr;
  T& operator [](size_t i) {} //Paramètre sous-entendu : VectorInt* this
};

template <typename T>
void contruireVector(Vector<T>* p_v, size_t taille, T val) {}

template <typename T>
void detruireVector(Vector<T>* p_v) {}

template <typename T>
size_t taille(Vector<T>* p_v) {}

template <typename T>
size_t capacite(Vector<T>* p_v) {}

template <typename T>
void reserver(Vector<T>* p_v, size_t nouvelleCapacite) {}

template <typename T>
void changerTaille(Vector<T>* p_v, size_t nouvelleTaille, T val) {}

template <typename T>
void ajouterFin(Vector<T>* p_v, T val) {}

template <typename T>
void enleverFin(Vector<T>* p_v) {}
