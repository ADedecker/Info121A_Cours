#include <iostream>

struct VectorInt{
  int* debut;
  int* fin;
};

//Partie 1
bool initVectorInt(VectorInt* p_v, size_t taille, int val = 0);
void supprimerVectorInt(VectorInt* p_v);
size_t taille(VectorInt* p_v);
int lire(VectorInt* p_v, size_t i);
void ecrire(VectorInt* p_v, size_t i, int val);

//Partie 2
bool changeTaille(VectorInt* p_v, size_t nouvelleTaille, int val = 0);
bool ajouteFin(VectorInt* p_v, int val = 0);

/*Partie 3 bonus
- Itroduire concept de capacité : zone allouée mais ne faisant pas partie du tableau
- fonctions capacite, reserver, libererSurplus (shrink_to_fit)
- Allez lire la doc et amusez vous !
*/
