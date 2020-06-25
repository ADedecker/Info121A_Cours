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

void merge(Liste* src1, Liste* src2, Liste* dest) {
  if(src1->p_debut == nullptr) {
    *dest = *src2; return;
  }
  if(src2->p_debut == nullptr) {
    *dest = *src1; return;
  }
  Noeud* p_premier;
  if(src1->p_debut->valeur <= src2->p_debut->valeur) {
    p_premier = src1->p_debut;
    src1->p_debut = p_premier->p_suivant;
    p_premier->p_suivant = nullptr;
  } else {
    p_premier = src2->p_debut;
    src2->p_debut = p_premier->p_suivant;
    p_premier->p_suivant = nullptr;
  }
  merge(src1,src2,dest);
  p_premier->p_suivant = dest->p_debut;
  dest->p_debut = p_premier;
}

void merge_sort(Liste* p_liste, size_t taille) {
  //std::cout<<taille<<std::endl;
  if(p_liste->p_debut == nullptr) return;
  if(p_liste->p_debut->p_suivant == nullptr) return;
  Liste premierePartie, deuxiemePartie;

  size_t coupure = taille/2;
  Noeud* it_coupure = p_liste->p_debut;
  for (int i = 0; i < coupure-1; i++) {
    it_coupure = it_coupure->p_suivant;
  }
  premierePartie.p_debut = p_liste->p_debut;
  deuxiemePartie.p_debut = it_coupure->p_suivant;
  it_coupure->p_suivant = nullptr;

  merge_sort(&premierePartie, taille/2);
  merge_sort(&deuxiemePartie, taille-taille/2);

  merge(&premierePartie,&deuxiemePartie,p_liste);
}

void merge_sort(Liste* p_liste) {
  size_t taille = 0;
  Noeud* it = p_liste->p_debut;
  while(it != nullptr)
}

int main() {
  Liste a;
  construireListeVide(&a);
  insererDebut(&a,42);
  insererDebut(&a,666);
  insererDebut(&a,-6);
  insererDebut(&a,2);
  insererDebut(&a,3);
  insererDebut(&a,1);
  afficherListe(&a);
  merge_sort(&a,6);
  std::cout<<"======"<<std::endl;
  afficherListe(&a);
  detruireListe(&a);
  return 0;
}
