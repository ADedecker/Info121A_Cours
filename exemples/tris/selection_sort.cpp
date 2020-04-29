#include <iostream>
#include <utility> // Pour swap

using namespace std;

void display_tab(int tab[], int taille) {
  for (int i = 0; i < taille; i++) {
    cout<<tab[i]<<";";
  }
  cout<<endl;
}

/** selection_sort
 *  @param[in/out] tab : un tableau d'entiers à trier par ordre croissant
 *                 (RAPPEL : les tableaux C sont toujours passés par référence)
 *  @param[in] taille : la taille du tableau
 **/
void selection_sort(int tab[], int taille) {
  for (int frontiere = 0; frontiere < taille-1; frontiere++) {
    int posmin = frontiere;
    for (int pos = frontiere+1; pos < taille; pos++) {
      if(tab[pos]<tab[posmin]) posmin = pos;
    }
    swap(tab[frontiere],tab[posmin]);
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  selection_sort(a,6);
  display_tab(a,6);
  // On doit afficher : -6;1;2;3;42;666
  return 0;
}
