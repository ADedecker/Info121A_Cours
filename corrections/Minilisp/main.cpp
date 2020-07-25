#include <iostream>

#include "interactive.hpp"

int main(int argc, char const *argv[]) {
  std::cout<<"Tutturuu !"<<std::endl;
  std::string folder;
  if(argc > 1) folder = argv[1];
  InteractiveSession session{{nullptr},folder};
  std::string instruction;
  do {
    std::cout << ">>> ";
    std::getline(std::cin,instruction);
  } while(execute(&session,instruction,std::cout));
  destroyInteractiveSession(&session);
}
