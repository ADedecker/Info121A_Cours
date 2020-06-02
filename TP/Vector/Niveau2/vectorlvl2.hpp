#include <iostream>

template <typename T> // On fait un modèle de classe pour tout type T
struct Vector {
  T* debut = nullptr;
  T* fin = nullptr;
  T* finCap = nullptr;
  T& operator [](size_t i) {} //Paramètre sous-entendu : VectorInt* this
};

template <typename T>
void initVector(Vector<T>* p_v, size_t taille, T val) {}

template <typename T>
void supprimerVector(Vector<T>* p_v) {}

template <typename T>
size_t taille(Vector<T>* p_v) {}

template <typename T>
size_t capacite(Vector<T>* p_v) {}

template <typename T>
void reserver(Vector<T>* p_v, size_t nouvelleCapacite) {}

template <typename T>
void changeTaille(Vector<T>* p_v, size_t nouvelleTaille, T val) {}

template <typename T>
void ajouteFin(Vector<T>* p_v, T val) {}

template <typename T>
void enleveFin(Vector<T>* p_v) {}
