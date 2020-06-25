#include <iostream>
#include <utility>

struct Noeud {
  int valeur;
  Noeud* p_suivant;
};

struct Liste {
  Noeud* p_debut;
};

bool construireListeVide(Liste* p_liste) {
  p_liste->p_debut = nullptr;
  return true;
}

bool insererDebut(Liste* p_liste, int val) {
  Noeud* nouveauDebut = (Noeud*)malloc(sizeof(Noeud));
  if(nouveauDebut == nullptr) return false;
  * nouveauDebut = {val, p_liste->p_debut};
  p_liste->p_debut = nouveauDebut;
  return true;
}

void detruireListe(Liste* p_liste) {
  while(p_liste->p_debut != nullptr) {
    Noeud* tmp = p_liste->p_debut->p_suivant;
    free(p_liste->p_debut);
    p_liste->p_debut = tmp;
  }
}

void afficherListe(Liste* p_liste) {
  Noeud* it = p_liste->p_debut;
  while(it != nullptr) {
    std::cout<< it->valeur <<std::endl;
    it = it->p_suivant;
  }
}

//////////////////////////////////////////

void merge(Liste* src1, Liste* src2, Liste* dest);

void merge_sort(Liste* p_liste, size_t taille);

void merge_sort(Liste* p_liste);

int main() {

  return 0;
}
