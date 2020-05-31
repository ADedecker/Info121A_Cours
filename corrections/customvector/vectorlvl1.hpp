#include <iostream>

struct VectorInt{
  int* debut = nullptr;
  int* fin = nullptr;
};

//Partie 1

/* Pseudo-constructeur de VectorInt
 * @param VectorInt* : un pointeur vers le vecteur à initialiser
 * @param size_t : la taille initiale du vecteur
 * @param int : la valeur initiale des cases du vecteur (0 par défaut)
 * @return bool : true si et seulement si l'initialisation s'est bien passée
 */
bool initVectorInt(VectorInt* p_v, size_t taille, int val = 0);


void supprimerVectorInt(VectorInt* p_v);


size_t taille(VectorInt* p_v);


int lire(VectorInt* p_v, size_t i);


void ecrire(VectorInt* p_v, size_t i, int val);

//Partie 2


bool changeTaille(VectorInt* p_v, size_t nouvelleTaille, int val = 0);


bool ajouteFin(VectorInt* p_v, int val = 0);
