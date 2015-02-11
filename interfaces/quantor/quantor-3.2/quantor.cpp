#include "quantor.h"

class QuantorWrapper {
  Quantor *const  q;

  //+ Construction / Destruction +++++++++++++++++++++++++++++++++++++++++++++
public:
  QuantorWrapper() q(quantor_new()) {}
  ~QuantorWrapper() {
    quantor_delete(q);
  }

private:
  void addLiteral(unsigned const  lit) { quantor_add(q, lit); }
  template<typename IT>
  void addLiterals(IT  lits) {
    while(true) {
      unsigned const  lit = *lits++;
      addLiteral(lit);
      if(lit == 0)  break;
    }
  }
  
public:
  template<typename IT>
  void declareVars(IT  cfgs,
		   IT  inputs,
		   II  nodes) {

    // Configuration Variables
    quantor_scope(q, QUANTOR_EXISTENTIAL_VARIABLE_TYPE);
    addLiterals(cfgs);

    // Input Variables
    quantor_scope(q, QUANTOR_UNIVERSAL_VARIABLE_TYPE);
    addLiterals(inputs);

    // Remaining Nodes (Internal and Outputs)
    quantor_scope(q, QUANTOR_EXISTENTIAL_VARIABLE_TYPE);
    addLiterals(nodes);
  }

  template<typename IT>
  void addClause(IT  lits) {
    addLiterals(lits);
  }

  int const* solve() {
    if(quantor_sat(q) != QUANTOR_RESULT_SATISFIABLE)  return  0;
    return  quantor_assignment(q);
  }
}
