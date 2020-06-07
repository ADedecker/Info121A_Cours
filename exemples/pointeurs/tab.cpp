#include <iostream>

using namespace std;

void initialiseTab(int* tab, size_t taille) {
  for (size_t i = 1; i < taille; i++) {
    tab[i] = i;
  }
}

void afficheTab(int tab[], size_t taille) {
  for (size_t i = 0; i < taille; i++) {
    std::cout<<tab[i]<<std::endl;
  }
}

int main() {
  int tab[10];
  initialiseTab(tab,10);
  afficheTab(tab,10);
  cout<<tab<<endl;
}
