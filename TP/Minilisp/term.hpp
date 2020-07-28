#ifndef TERM_HPP
#define TERM_HPP

#include <iostream>

//Une structure correspondant aux différentes erreurs possibles
struct MinilispError {
  enum Type {INVALID_HEADER, EXPECTED_TERM, ARITY_ERROR, UNKNOWN_SYMBOL, ALLOCATION_FAILED, NOT_IMPLEMENTED} type;
  std::string msg;
};

//Une valeur Minilisp est un entier long
using Val = long;

//Les opérateurs de base du langage
enum BuiltinOp {ADD, SUB, MUL, DIV, MOD, EQ, NEQ, SUP, SUPEQ, INF, INFEQ, NOT, AND, OR, IF};

//On déclare des structures qu'on définira plus tard de manière à pouvoir parler des types Term* et Funcction*
struct Term;
struct Function;

//Une variable = son indice dans le tableau des variables
struct Variable{
  size_t id;
};

//Une opération = opérateur + tableau de paramètres
struct Operation{
  BuiltinOp op;
  Term* parameters;
};

//Un appel de fonction = Terme de la fonction + tableau de paramètres
struct Call{
  Function* p_function;
  Term* parameters;
};

//Un terme = une valeur OU une variable OU une opération OU un appel de fonction
struct Term{
  enum {VALUE, VARIABLE, OPERATION, CALL} tag = VALUE;
  union {
    Val value;
    Variable variable;
    Operation operation;
    Call call;
  } data;
};

//Une fonction = un terme + nombre de paramètres
struct Function {
  Term term;
  size_t n_params;
};

void initValueTerm(Term* p_term, Val val);
void initVariableTerm(Term* p_term, size_t id);
void initOperationTerm(Term* p_term, BuiltinOp op, Term* parameters);
void initCallTerm(Term* p_term, Function* p_function, Term* parameters);

void destroyTerm(Term* ptr);
void destroyFunction(Function* ptr);

size_t n_params_op(BuiltinOp op);

#endif
