#include <iostream>

struct VectorInt{
  int* debut = nullptr;
  int* fin = nullptr;
};

//Partie 1

/* Pseudo-constructeur de VectorInt
 * Initialise une variable VectorInt
 * @param VectorInt* : un pointeur vers le vecteur à initialiser
 * @param size_t : la taille initiale du vecteur
 * @param int : la valeur initiale des cases du vecteur (0 par défaut)
 * @return bool : true si et seulement si l'initialisation s'est bien passée
 */
bool construireVectorInt(VectorInt* p_v, size_t taille, int val = 0);

/* Pseudo-destructeur de VectorInt
 * Prépare la supression d'une variable VectorInt
 * @param VectorInt* : un pointeur vers le vecteur à détruire
 */
void detruireVectorInt(VectorInt* p_v);

/* Fonction taille
 * Renvoie le nombre d'éléments d'un VectorInt
 * @param VectorInt* : un pointeur vers le vecteur
 * @return size_t : la taille du vecteur
 */
size_t taille(VectorInt* p_v);

/* Fonction lire
 * Renvoie le contenu d'une case d'un VectorInt
 * @param VectorInt* : un pointeur vers le vecteur
 * @param size_t : l'indice de la case à lire
 * @return int : le contenu de la case
 */
int lire(VectorInt* p_v, size_t i);

/* Fonction ecrire
 * Modifie le contenu d'une case d'un VectorInt
 * @param VectorInt* : un pointeur vers le vecteur
 * @param size_t : l'indice de la case à écrire
 * @param int : la valeur à écrire
 */
void ecrire(VectorInt* p_v, size_t i, int val);

//Partie 2

/* Fonction changerTaille
 * Change la taille d'un VectorInt
 * @param VectorInt* : un pointeur vers le vecteur
 * @param size_t : la nouvelle taille
 * @param int : la valeur par défaut pour les cases créées (si il y en a)
 * @return bool : true si et seulement si le changement de taille a marché
 */
bool changerTaille(VectorInt* p_v, size_t nouvelleTaille, int val = 0);

/* Fonction ajouterFin
 * Ajoute un élément à la fin d'un VectorInt
 * @param VectorInt* : un pointeur vers le vecteur
 * @param int : la valeur à ajouter
 * @return bool : true si et seulement si l'ajout a marché
 */
bool ajouterFin(VectorInt* p_v, int val = 0);
