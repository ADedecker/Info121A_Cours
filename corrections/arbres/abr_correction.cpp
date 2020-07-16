#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct Noeud {
  int val;
  Noeud* p_gauche;
  Noeud* p_droite;
};

struct ArbreBinaire {
  Noeud* p_racine;
};

bool construireABRVide(ArbreBinaire* p_arbre) {
  p_arbre->p_racine = nullptr;
  return true;
}

bool rechercherABR(ArbreBinaire* p_arbre, int val) {
  Noeud* it = p_arbre->p_racine;
  while(it != nullptr) {
    if(it->val == val) return true;
    if(it->val > val) it = it->p_gauche;
    else it = it->p_droite;
  }
  return false;
}

bool insererABR(ArbreBinaire* p_arbre, int val) {
  Noeud** ptr_a_modifier = &(p_arbre->p_racine);
  Noeud* it = *ptr_a_modifier;
  while(it != nullptr) {
    if(it->val == val) return true;
    if(it->val > val) ptr_a_modifier = &(it->p_gauche);
    else ptr_a_modifier = &(it->p_droite);
    it = *ptr_a_modifier;
  }
  *ptr_a_modifier = (Noeud*)malloc(sizeof(Noeud));
  if(*ptr_a_modifier == nullptr) return false;
  **ptr_a_modifier = {val, nullptr, nullptr};
  return true;
}

void afficherABR(Noeud* p_noeud) {
  if(p_noeud == nullptr) return;
  afficherABR(p_noeud->p_gauche);
  cout<<p_noeud->val<<" ";
  afficherABR(p_noeud->p_droite);
}

void afficherABR(ArbreBinaire* p_arbre) {
  afficherABR(p_arbre->p_racine);
  cout<<endl;
}

int profondeurMaxABR(Noeud* p_noeud) {
  if(p_noeud == nullptr) return 0;
  return 1+max(profondeurMaxABR(p_noeud->p_gauche),profondeurMaxABR(p_noeud->p_droite));
}

int profondeurMaxABR(ArbreBinaire* p_arbre) {
  return profondeurMaxABR(p_arbre->p_racine);
}

int main() {
  srand(time(nullptr));
  int n = 1000000;

  ArbreBinaire abr;
  construireABRVide(&abr);

  for (int i = 0; i < n; i++) {
    insererABR(&abr,rand()%n);
  }

  afficherABR(&abr);
  cout<<rechercherABR(&abr,n/2)<<endl;
  cout<<profondeurMaxABR(&abr)<<endl;
}
