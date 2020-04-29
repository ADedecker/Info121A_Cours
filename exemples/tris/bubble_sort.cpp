#include <iostream>
#include <utility> // Pour swap

using namespace std;

void display_tab(int tab[], int taille) {
  for (int i = 0; i < taille; i++) {
    cout<<tab[i]<<";";
  }
  cout<<endl;
}

/** bubble_sort
 *  @param[in/out] tab : un tableau d'entiers à trier par ordre croissant
 *                 (RAPPEL : les tableaux C sont toujours passés par référence)
 *  @param[in] taille : la taille du tableau
 **/
void bubble_sort(int tab[], int taille) {
  bool trie = false;
  while(!trie) {
    trie = true;
    for (int i = 0; i < taille-1; i++) {
      if(tab[i]>tab[i+1]) {
        swap(tab[i],tab[i+1]);
        trie = false;
      }
    }
  }
}

int main() {
  int a[]{1,3,2,-6,666,42};
  bubble_sort(a,6);
  display_tab(a,6);
  // On doit afficher : -6;1;2;3;42;666
  return 0;
}
