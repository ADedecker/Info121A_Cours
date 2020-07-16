#include <iostream>

bool recherche(int* p_begin, int* p_end, int val) {
  while(p_begin != p_end) {
    if(*p_begin == val) return true;
    p_begin++;
  }
  return false;
}

bool recherche_dichotomique_rec(int* p_begin, int* p_end, int val) {
  if(p_begin == p_end) return false;
  int* p_middle = p_begin+(p_end-p_begin)/2;
  if(*p_middle == val) return true;
  if(*p_middle < val) return recherche_dichotomique_rec(p_middle + 1, p_end, val);
  return recherche_dichotomique_rec(p_begin, p_middle, val);
}

bool recherche_dichotomique_iter(int* p_begin, int* p_end, int val) {
  while(p_begin != p_end) {
    int* p_middle = p_begin+(p_end-p_begin)/2;
    if(*p_middle == val) return true;
    if(*p_middle < val) p_begin = p_middle+1;
    else p_end = p_middle;
  }
  return false;
}

int main() {
  int tab[]{-6,12,1,5,3,42};
  std::cout<<recherche(tab,tab+6,3)<<std::endl;
  int tab2[]{-6,1,3,4,12,42};
  std::cout<<recherche_dichotomique_rec(tab2,tab2+6,3)<<std::endl;
  std::cout<<recherche_dichotomique_iter(tab2,tab2+6,3)<<std::endl;
  return 0;
}