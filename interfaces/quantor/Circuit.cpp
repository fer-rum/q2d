#include "Circuit.hpp"
#include "Context.hpp"

Iterator<unsigned> Circuit::getConfigs()  const {
  static unsigned const  CFGS[] = { 1, 2, 3, 4 };
  return  Iterator<unsigned>(CFGS, CFGS+4);
}

Iterator<unsigned> Circuit::getInputs()   const {
  static unsigned const  INS[] = { 5, 6 };
  return  Iterator<unsigned>(INS, INS+2);
}

Iterator<unsigned> Circuit::getNodes()    const {
  static unsigned const  NODES[] = { 7 };
  return  Iterator<unsigned>(NODES, NODES+1);
}

Iterator<Context>  Circuit::getContexts() const {
  static Context  ctx;
  return  Iterator<Context>(&ctx, &ctx+1);
}
