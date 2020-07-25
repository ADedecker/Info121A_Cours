#ifndef INTERACTIVE_HPP
#define INTERACTIVE_HPP

#include <fstream>

#include "term.hpp"
#include "parser.hpp"
#include "evaluation.hpp"

struct InteractiveSession {
  FunctionPool pool;
  std::string path_prefix;
};

bool execute(InteractiveSession* session, std::string instruction, std::ostream& out);
void destroyInteractiveSession(InteractiveSession* session);

#endif
