#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>

#include "term.hpp"

/* L'ensembles des variables valides dans le contexte. Cet ensemble est utilisé
  par le parser pour générer le terme d'une fonction à paramètres */

struct VariableListNode{
  std::string name;
  VariableListNode* p_next;
};

struct VariablePool{
  VariableListNode* p_begin;
  VariableListNode** p_last_pointer;
};

void initEmptyVariablePool(VariablePool* pool);
void addVariableToPool(VariablePool* pool, std::string name);
int searchVariableInPool(VariablePool* pool, std::string name);
void clearVariablePool(VariablePool* pool);

/* L'ensembles des fonctions déclarées ou chargées depuis un fichier.
  Cet ensemble est utilisé par le parser lors de l'analyse d'appels de fonction */

struct FunctionTreeNode{
  std::string name;
  Function function;
  FunctionTreeNode* p_left;
  FunctionTreeNode* p_right;
};

struct FunctionPool{
  FunctionTreeNode* p_root;
};

void initEmptyFunctionPool(FunctionPool* pool);
Function* addFunctionToPool(FunctionPool* pool, std::string name);
void listFunctions(FunctionTreeNode* p_node);
void listFunctions(FunctionPool* pool);
Function* searchFunctionInPool(FunctionPool* pool, std::string name);
void clearFunctionPool(FunctionTreeNode* p_node);
void clearFunctionPool(FunctionPool* pool);

/* Les fonctions clés du parser */

//Parse un symbole atomique (valeur ou variable)
void parseAtomic(Term* p_term, std::string atom, VariablePool* varPool);

//Parse un terme quelconque, dans un certain contexte (donné par l'ensemble des fonctions et variables déclarées)
void parseTerm(Term* p_term, std::istream& stream, FunctionPool* functionPool, VariablePool* varPool);

//Parse et charge une nouvelle fonction
void loadNewFunction(std::istream& stream, FunctionPool* functionPool);

#endif
