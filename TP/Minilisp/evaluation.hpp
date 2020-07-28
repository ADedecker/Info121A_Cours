#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include "term.hpp"

#include <iostream>

Val evalTerm(Term t, Val* varpool = nullptr);

#endif
