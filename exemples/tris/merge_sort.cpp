#include <iostream>
#include <utility>

// Copions d'abord tout ce dont on a besoin pour manipuler des listes

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

// On peut passer au tri

void merge(Liste* src1, Liste* src2, Liste* dest) {
  //On suppose qu'à chaque appel de cette fonction, les listes *src1 et *src2 sont
  //les uniques propriétaires de leurs noeuds, et que *dest n'est pas propriétaire
  //(i.e aucun free ne sera fait sur les éventuels éléments de cette liste)
  //De plus, à la fin de la fonction, la liste *dest aura pris la propriété des
  //noeuds des listes *src1 et *src2, qui ne seront donc plus propriétaires
  //d'aucun noeud, i.e aucun free ne doit être fait sur leurs noeuds
  //éventuels (vous pouvez vérifier que c'est le cas)

  if(src1->p_debut == nullptr) {
    *dest = *src2; return;
    //Transfert de propriété : tous les noeuds de *src2 appartiennent désormais
    //à *dest. Encore une fois, pour être parfaitement dans les clous, il
    //faudrait écrire :
    //src2->p_debut = nullptr;
    //Mais ici aussi, ce serait inutile, puisque qu'on s'est seulement engagés
    //à ce que *dest soit propriétaire de tous les noeuds de *src1 et *src2, ce
    //qui est le cas
  }
  if(src2->p_debut == nullptr) {
    *dest = *src1; return;
    //Même remarque qu'au dessus
  }
  Noeud* p_premier;
  if(src1->p_debut->valeur <= src2->p_debut->valeur) {
    p_premier = src1->p_debut;
    src1->p_debut = src1->p_debut->p_suivant;
    p_premier->p_suivant = nullptr;
    //Ici, la liste *src1 transfère la propriété de son premier noeud au
    //pointeur p_premier. Cela nécessite de supprimer le lien entre ce noeud
    //et son suivant, de manière à ce que chaque noeud ait un unique propriétaire
  } else {
    p_premier = src2->p_debut;
    src2->p_debut = src2->p_debut->p_suivant;
    p_premier->p_suivant = nullptr;
    //Même remarque que ci-dessus
  }

  //La liste *dest est bien non-propriétaire
  //On est donc dans les bonnes conditions pour appeler la fonction
  merge(src1,src2,dest);
  //Après cet appel de fonction, la liste *dest a récupérer la propriété des noeuds
  //de *src1 et *src2. Ces deux listes n'étant plus propriétaires, on peut, et on
  //doit, ne pas les libérer

  p_premier->p_suivant = dest->p_debut;
  dest->p_debut = p_premier;
  //Enfin, *dest récupère récupère aussi la propriété de *p_premier
  //On a donc respecté nos engagements : *src1 et *src2 sont non-propriétaires,
  //et *dest a récupéré la propriété de tous leurs noeuds
}

void merge_sort(Liste* p_liste, size_t taille) {
  //On suppose qu'à tout appel, la liste *p_liste est l'unique propriétaire
  //de l'ensemble de ses noeuds.
  //De plus, à la fin de cette fonction, on s'engage à ce que *p_liste soit
  //l'unique propriétaires des mêmes noeuds que ce qu'elle possède au début

  if(p_liste->p_debut == nullptr) return;
  if(p_liste->p_debut->p_suivant == nullptr) return;

  Liste premierePartie, deuxiemePartie;

  construireListeVide(&premierePartie);
  construireListeVide(&deuxiemePartie);

  Noeud* it = p_liste->p_debut;
  for (int i = 0; i < taille/2 - 1; i++) {
    it = it->p_suivant;
  }
  premierePartie.p_debut = p_liste->p_debut;
  deuxiemePartie.p_debut = it->p_suivant;
  it->p_suivant = nullptr;
  //Transfert de propriété : la première moitié des noeuds appartiennent
  //maintenant à premierePartie, l'autre moitié à deuxiemePartie
  //C'est le cas car on a fait la séparation : on ne peut plus accéder aux noeuds
  //de la deuxième partie en itérant depuis la première, donc chaque noeud
  //appartient à une seule des deux listes. Pour que cette affirmation soit
  //totalement vraie, il faudrait cependant écrire :
  //p_liste->p_debut = nullptr;
  //pour souligner que p_liste n'a plus la propriété d'aucun noeud
  //Mais cette instruction est en réalité inutile, puisque la seule utilisation
  //restante de cette liste est faite par la fonction `merge`, qui assumera de
  //toutes façons que cette liste ne possède rien. Pas de risque de double free
  //donc.

  //Comme promis, les autres appels à merge_sort sont bien faits sur des listes
  //qui sont les uniques propriétaires de leurs noeuds
  merge_sort(&premierePartie, taille/2);
  merge_sort(&deuxiemePartie, taille - taille/2);
  //Notons aussi que l'on sait, à l'issue de ces appels, que premierePartie et
  //deuxiemePartie sont toujours propriétaires des mêmes noeuds

  //Vérifions d'abord les conditions préalables d'appel : les deux premières listes
  //sont propriétaires uniques, la dernière n'est pas propriétaire
  merge(&premierePartie,&deuxiemePartie,p_liste);
  //Après cet appel, on est garanti que la dernière liste a récupéré la propriété
  //de tous les noeuds des deux premières. On ne libère donc aucun noeud, et
  //*p_liste a récupéré la possession de tous les noeuds qu'elle possédait initialement
}

//void merge_sort(Liste* p_liste);

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
