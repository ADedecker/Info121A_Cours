#include <iostream>

#include "vectorlvl2.hpp"

using namespace std;

int main() {
  Vector<int> v;
  initVector(&v,10,1);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  ajouteFin(&v,2);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  cout<<v[10]<<endl;
  changeTaille(&v, 1ul<<16, 42);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  cout<<v[10]<<endl;
  cout<<v[11]<<endl;
  supprimerVector(&v); //Démo en supprimant + getchar
  return 0;
}
