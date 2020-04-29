#include <iostream>
#include <utility> // Pour swap

using namespace std;

void display_tab(int tab[], int taille) {
  for (int i = 0; i < taille; i++) {
    cout<<tab[i]<<";";
  }
  cout<<endl;
}

/** insertion_sort
 *  @param[in/out] tab : un tableau d'entiers à trier par ordre croissant
 *                 (RAPPEL : les tableaux C sont toujours passés par référence)
 *  @param[in] taille : la taille du tableau
 **/
void insertion_sort(int tab[], int taille) {
  for (int frontiere = 1; frontiere < taille; frontiere++) {
    int pos = frontiere;
    while(pos>0 && tab[pos-1]>tab[pos]) {
      swap(tab[pos-1],tab[pos]);
      pos--;
    }
  }
}

// Version recherche PUIS décalage
void insertion_sort_search_shift(int tab[], int taille) {
  for (int frontiere = 1; frontiere < taille; frontiere++) {
    int val = tab[frontiere];
    int newpos = 0;
    while(tab[newpos]<=val && newpos<frontiere) newpos++;
    for (int i = frontiere; i > newpos; i--) {
      tab[i]=tab[i-1];
    }
    tab[newpos]=val;
  }
}

// Version recherche ET décalage en même temps
void insertion_sort_shift(int tab[], int taille) {
  for(int pos = 1; pos<taille; pos++) {
    int val = tab[pos];
    int newpos = pos;
    while(newpos > 0 && tab[newpos-1]>val) {
      tab[newpos]=tab[newpos-1];
      newpos--;
    }
    tab[newpos] = val;
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  insertion_sort_shift(a,6);
  display_tab(a,6);
  // On doit afficher : -6;1;2;3;42;666
  return 0;
}
