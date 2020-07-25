#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include "term.hpp"

#include <iostream>

Val evalTerm(Term t, Val* varpool = nullptr);
Val evalBuiltinOp(BuiltinOp op, Term* params, Val* varpool = nullptr);
Val evalFunctionCall(Function* function, Term* params, Val* varpool = nullptr);

#endif
