#include <iostream>

#include "vectorlvl2.hpp"

using namespace std;

int main() {
  Vector<int> v;
  construireVector(&v,10,1);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  ajouterFin(&v,2);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  cout<<v[10]<<endl;
  changerTaille(&v, 1ul<<16, 42);
  cout<<taille(&v)<<endl;
  cout<<capacite(&v)<<endl;
  cout<<v[9]<<endl;
  cout<<v[10]<<endl;
  cout<<v[21]<<endl;
  detruireVector(&v); //Démo en supprimant + getchar
  return 0;
}
