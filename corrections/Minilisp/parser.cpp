#include "parser.hpp"

void parseAtomic(Term* p_term, std::string atom, VariablePool* varpool) {
  if(atom == "true") initValueTerm(p_term, 1);
  else if(atom == "false") initValueTerm(p_term, 0);
  else {
    try{
      initValueTerm(p_term, std::stol(atom));
    }catch(...){
      if(varpool != nullptr) {
        int i = searchVariableInPool(varpool, atom);
        if(i>=0) {
          initVariableTerm(p_term, (size_t)i);
          return;
        }
      }
      throw MinilispError{MinilispError::UNKNOWN_SYMBOL, "Symbole atomique "+atom+" inconnu"};
    }
  }
}

void parseTerm(Term* p_term, std::istream& stream, FunctionPool* functionPool, VariablePool* varpool) {
  static int tab = -1;
  if(!stream || stream.eof()) {std::cerr<<"Expected term"<<std::endl; throw MinilispError{MinilispError::EXPECTED_TERM,"Terme attendu : fin du fichier atteinte"};}
  tab++;
  std::string first_block, second_block, tmp;
  bool is_atomic = true;
  std::stringstream first_block_stream;
  if(stream.peek() == '(') {
    is_atomic = false;
    stream.get();
  }
  char c = stream.peek();
  while(stream && !stream.eof() && !std::isspace(c) && c != ')') {
    first_block_stream << c;
    stream.get();
    c = stream.peek();
  }
  first_block = first_block_stream.str();
  if(is_atomic) {
    parseAtomic(p_term,first_block,varpool);
  }else{
    BuiltinOp op;
    Function* p_function;
    bool is_call = false;
    if(first_block == "+" || first_block == "add") op = ADD;
    else if(first_block == "-" || first_block == "sub") op = SUB;
    else if(first_block == "*" || first_block == "mul") op = MUL;
    else if(first_block == "/" || first_block == "div") op = DIV;
    else if(first_block == "%" || first_block == "mod") op = MOD;
    else if(first_block == "=" || first_block == "eq") op = EQ;
    else if(first_block == "!=" || first_block == "neq") op = NEQ;
    else if(first_block == ">") op = SUP;
    else if(first_block == ">=") op = SUPEQ;
    else if(first_block == "<") op = INF;
    else if(first_block == "<=") op = INFEQ;
    else if(first_block == "!" || first_block == "not") op = NOT;
    else if(first_block == "&&" || first_block == "and") op = AND;
    else if(first_block == "||" || first_block == "or") op = OR;
    else if(first_block == "?"  || first_block == "if") op = IF;
    else {
      is_call = true;
      p_function = searchFunctionInPool(functionPool, first_block);
      if (p_function == nullptr) throw MinilispError{MinilispError::UNKNOWN_SYMBOL,"Symbole non-atomique "+first_block+" inconnu"};
    }

    size_t n_params = is_call ? p_function->n_params : n_params_op(op);
    Term* params;

    try{
      params = new Term[n_params];
    }catch(...){
      throw MinilispError{MinilispError::ALLOCATION_FAILED,"Erreur d'allocation. Lib??rez de la m??moire."};
    }

    stream >> std::ws;
    size_t i = 0;
    try{
      while(stream && !stream.eof() && stream.peek() != ')'){
        if (i>=n_params) {
          throw MinilispError{MinilispError::ARITY_ERROR,"Erreur d'arit?? : le symbole "+first_block+" attend "+std::to_string(n_params)+" param??tres"};
        }
        parseTerm(params+i, stream, functionPool, varpool);
        stream >> std::ws;
        ++i;
      }
      stream.get(); //On extrait la parenth??se
      if(i < n_params) {
        //std::cerr<<"Arity error"<<std::endl;
        throw MinilispError{MinilispError::ARITY_ERROR, "Erreur d'arit?? : le symbole "+first_block+" attend "+std::to_string(n_params)+" param??tres"};
      }
      try{
        //Il faut que les sous-termes soient form??s avant cette ligne :
        if (is_call) initCallTerm(p_term, p_function, params);
        else initOperationTerm(p_term, op, params);
      }catch(MinilispError& e){
        e.msg = std::string() + "Erreur de type dans les param??tres de " + (is_call ? "la fonction " : "l'op??rateur ") + first_block + " : " + e.msg;
        throw e;
      }
    }catch(MinilispError& e){
      for (int j = 0; j < i; j++) {
        destroyTerm(params+j); //On d??truit ceux qu'on avait bien construits
      }
      delete params;
      throw e;
    }
  }
  tab--;
}

void initEmptyVariablePool(VariablePool* pool) {
  pool->p_begin = nullptr;
  pool->p_last_pointer = &(pool->p_begin);
}

void addVariableToPool(VariablePool* pool, std::string name) {
  try {
    *(pool->p_last_pointer) = new VariableListNode{name,nullptr};
    pool->p_last_pointer = &((*(pool->p_last_pointer))->p_next);
  }
  catch(...) {
    throw MinilispError{MinilispError::ALLOCATION_FAILED, "Erreur d'allocation. Lib??rez de la m??moire."};
  }
}

int searchVariableInPool(VariablePool* pool, std::string name) {
  VariableListNode* it = pool->p_begin;
  int i = 0;
  while(it != nullptr) {
    if(it->name == name) return i;
    i++;
    it = it->p_next;
  }
  return -1;
}

void clearVariablePool(VariablePool* pool) {
  VariableListNode* tmp = pool->p_begin;
  while(pool->p_begin != nullptr) {
    pool->p_begin = pool->p_begin->p_next;
    delete tmp;
    tmp = pool->p_begin;
  }
  pool->p_last_pointer = &(pool->p_begin);
}

void loadNewFunction(std::istream& stream, FunctionPool* functionPool) {
  Function* p_function;
  std::string name;
  std::string header;
  std::getline(stream,header,':');
  stream >> std::ws;
  std::istringstream header_stream(header);
  VariablePool varpool;
  initEmptyVariablePool(&varpool);
  header_stream >> name;
  header_stream >> std::ws;
  size_t n_params = 0;
  while(header_stream.get() == '[') {
    ++n_params;
    std::string param;
    std::getline(header_stream,param,']');
    header_stream.get();
    header_stream >> std::ws;
    addVariableToPool(&varpool,param);
  }
  p_function = addFunctionToPool(functionPool, name);
  p_function->n_params = n_params;
  try{
    parseTerm(&(p_function->term),stream,functionPool,&varpool);
  }catch(MinilispError& e){
    clearVariablePool(&varpool);
    throw e;
  }
  clearVariablePool(&varpool);
}

void initEmptyFunctionPool(FunctionPool* pool) {
  pool->p_root = nullptr;
}

Function* addFunctionToPool(FunctionPool* pool, std::string name) {
  FunctionTreeNode** ptr_to_update = &(pool->p_root);
  FunctionTreeNode* it = pool->p_root;
  while(it != nullptr) {
    if(it->name == name) {destroyFunction(&(it->function)); return &(it->function); }
    if(it->name > name) {ptr_to_update = &(it->p_left); it = it->p_left;}
    else {ptr_to_update = &(it->p_right); it = it->p_right;}
  }
  try{
    *ptr_to_update = new FunctionTreeNode{name, {Term{}, 0}, nullptr, nullptr};
  } catch (...) {
    throw MinilispError{MinilispError::ALLOCATION_FAILED, "Erreur d'allocation. Lib??rez de la m??moire."};
  }
  return &((*ptr_to_update)->function);
}

void listFunctions(FunctionTreeNode* p_node) {
  if(p_node == nullptr) return;
  listFunctions(p_node->p_left);
  std::cout<<" "<<p_node->name<<" ["<<p_node->function.n_params<<"]"<<std::endl;
  listFunctions(p_node->p_right);
}

void listFunctions(FunctionPool* pool) {
  listFunctions(pool->p_root);
}

Function* searchFunctionInPool(FunctionPool* pool, std::string name) {
  FunctionTreeNode* it = pool->p_root;
  while(it != nullptr) {
    if(it->name == name) return &(it->function);
    if(it->name > name) it = it->p_left;
    else it = it->p_right;
  }
  return nullptr;
}

void clearFunctionPool(FunctionTreeNode* p_node) {
  if(p_node == nullptr) return;
  clearFunctionPool(p_node->p_left);
  clearFunctionPool(p_node->p_right);
  delete p_node;
}

void clearFunctionPool(FunctionPool* pool) {
  clearFunctionPool(pool->p_root);
}
