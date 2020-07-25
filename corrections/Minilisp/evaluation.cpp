#include "evaluation.hpp"

Val evalTerm(Term t, Val* var_values) {
  //std::cout<<var_values<<" ";
  switch (t.tag) {
    case Term::VALUE:
      //std::cout<<"V"<<std::endl;
      return t.value;
    case Term::VARIABLE:
      //std::cout<<"P"<<std::endl;
      return var_values[t.variable.id];
    case Term::OPERATION:
      //std::cout<<"O"<<std::endl;
      return evalBuiltinOp(t.operation.op, t.operation.parameters, var_values);
    case Term::CALL:
      //std::cout<<"C"<<std::endl;
      return evalFunctionCall(t.call.p_function, t.call.parameters, var_values);
  }
  return Val{};
}

Val evalBuiltinOp(BuiltinOp op, Term* p, Val* var_values) {
  switch (op) {
    case ADD:
      return evalTerm(p[0],var_values) + evalTerm(p[1],var_values);
    case SUB:
      return evalTerm(p[0],var_values) - evalTerm(p[1],var_values);
    case NEG:
      return -evalTerm(p[0],var_values);
    case MUL:
      return evalTerm(p[0],var_values) * evalTerm(p[1],var_values);
    case DIV:
      return evalTerm(p[0],var_values) / evalTerm(p[1],var_values);
    case MOD:
      return evalTerm(p[0],var_values) % evalTerm(p[1],var_values);
    case EQ:
      return evalTerm(p[0],var_values) == evalTerm(p[1],var_values);
    case NEQ:
      return evalTerm(p[0],var_values) != evalTerm(p[1],var_values);
    case SUP:
      return evalTerm(p[0],var_values) > evalTerm(p[1],var_values);
    case SUPEQ:
      return evalTerm(p[0],var_values) >= evalTerm(p[1],var_values);
    case INF:
      return evalTerm(p[0],var_values) < evalTerm(p[1],var_values);
    case INFEQ:
      return evalTerm(p[0],var_values) <= evalTerm(p[1],var_values);
    case NOT:
      return !evalTerm(p[0],var_values);
    case AND:
      return evalTerm(p[0],var_values) && evalTerm(p[1],var_values);
    case OR:
      return evalTerm(p[0],var_values) || evalTerm(p[1],var_values);
    case IF:
      if(evalTerm(p[0],var_values)) {
        return evalTerm(p[1],var_values);
      }else{
        return evalTerm(p[2],var_values);
      };
    case PRINT:
      Val ret = evalTerm(p[0],var_values);
      std::cout<<ret;
      return ret;
  }
}

Val evalFunctionCall(Function* p_function, Term* params, Val* var_values) {
  Val* new_var_values = new Val[p_function->n_params];
  for (size_t i = 0; i < p_function->n_params; i++) {
    new_var_values[i] = evalTerm(params[i], var_values);
  }
  Val ret = evalTerm(p_function->term, new_var_values);
  delete[] new_var_values;
  return ret;
}
