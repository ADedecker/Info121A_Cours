#include "term.hpp"

void initValueTerm(Term* p_term, Val value) {
  p_term->tag = Term::VALUE;
  p_term->value = value;
}

void initVariableTerm(Term* p_term, size_t id) {
  p_term->tag = Term::VARIABLE;
  p_term->variable.id = id;
}

void initOperationTerm(Term* p_term, BuiltinOp op, Term* parameters) {
  p_term->tag = Term::OPERATION;
  p_term->operation = {op, parameters};
}

void initCallTerm(Term* p_term, Function* p_function, Term* parameters) {
  p_term->tag = Term::CALL;
  p_term->call = {p_function, parameters};
}

void destroyTerm(Term* p_term) {
  switch (p_term->tag) {
    case Term::VALUE:
    case Term::VARIABLE:
      break;
    case Term::CALL:
      for(size_t i = 0; i < p_term->call.p_function->n_params ; i++) {
        destroyTerm(p_term->call.parameters + i);
      }
      delete[] p_term->call.parameters;
    case Term::OPERATION:
      for(size_t i = 0; i < n_params_op(p_term->operation.op) ; i++) {
        destroyTerm(p_term->operation.parameters + i);
      }
      delete[] p_term->operation.parameters;
  }
}

void destroyFunction(Function* ptr) {
  destroyTerm(&(ptr->term));
}

size_t n_params_op(BuiltinOp op) {
  switch (op) {
    case NEG:
    case NOT:
    case PRINT:
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
