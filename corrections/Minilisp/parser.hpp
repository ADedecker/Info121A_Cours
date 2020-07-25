#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>

#include "term.hpp"

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
void clearVariablePool(VariablePool* pool);

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

void parseAtomic(Term* p_term, std::string atom, VariablePool* varPool);
void parseTerm(Term* p_term, std::istream& stream, FunctionPool* functionPool, VariablePool* varPool);
void loadNewFunction(std::istream& stream, FunctionPool* functionPool);

#endif
