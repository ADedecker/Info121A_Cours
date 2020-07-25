#include "interactive.hpp"

bool execute(InteractiveSession* session, std::string instruction, std::ostream& out) {
  std::istringstream instruction_stream(instruction);
  std::string command;
  instruction_stream >> command;
  if(command == "quit") return false;
  if(command == "eval") {
    instruction_stream >> std::ws;
    try{
      Term t;
      parseTerm(&t, instruction_stream, &session->pool, nullptr);
      std::cout << evalTerm(t,nullptr) << std::endl;
    }catch(MinilispError& e){
      std::cout<<e.msg<<std::endl;
    }
  } else if(command == "load") {
    std::string filename;
    instruction_stream >> filename;
    std::ifstream filestr;
    filestr.open(session->path_prefix + filename + ".mlisp");
    if(!filestr) {
      out<<"This file doesn't exist"<<std::endl;
    }else{
      try {
        while(filestr && !filestr.eof()) {
          loadNewFunction(filestr, &session->pool);
          filestr >> std::ws;
        }
      }catch(MinilispError& e){
        std::cout<<e.msg<<std::endl;
      }
    }
  } else if(command == "defun") {
    instruction_stream >> std::ws;
    try {
      loadNewFunction(instruction_stream, &session->pool);
    }catch(MinilispError& e){
      std::cout<<e.msg<<std::endl;
    }
  } else if(command == "listfun") {
    listFunctions(&session->pool);
  } else {
    out<<"Unkonwn instruction"<<std::endl;
  }
  return true;
}

void destroyInteractiveSession(InteractiveSession* session) {
  clearFunctionPool(&session->pool);
}
