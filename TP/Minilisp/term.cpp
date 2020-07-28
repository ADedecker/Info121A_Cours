#include "term.hpp"

//Les 4 constructeurs du type Term

void initValueTerm(Term* p_term, Val value) {

}

void initVariableTerm(Term* p_term, size_t id) {

}

void initOperationTerm(Term* p_term, BuiltinOp op, Term* parameters) {

}

void initCallTerm(Term* p_term, Function* p_function, Term* parameters) {

}

//Destructeur du type Term

void destroyTerm(Term* p_term) {

}

//On détruit une fonction en détruisant son terme
void destroyFunction(Function* ptr) {
  destroyTerm(&(ptr->term));
}

//Le nombre de paramètres (arité) des opérateurs
size_t n_params_op(BuiltinOp op) {
  switch (op) {
    case NOT:
      return 1;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MOD:
    case EQ:
    case NEQ:
    case SUP:
    case SUPEQ:
    case INF:
    case INFEQ:
    case AND:
    case OR:
      return 2;
    case IF:
      return 3;
  }
}
