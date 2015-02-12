#include "Circuit.hpp"
#include "QIContext.h"

using namespace q2d::quantor;

Iterator<unsigned const*> Circuit::getConfigs()  const {
  static unsigned const  CFGS[] = { 1, 2, 3, 4 };
  return  Iterator<unsigned const*>(CFGS, CFGS+4);
}

Iterator<unsigned const*> Circuit::getInputs()   const {
  static unsigned const  INS[] = { 5, 6 };
  return  Iterator<unsigned const*>(INS, INS+2);
}

Iterator<unsigned const*> Circuit::getNodes()    const {
  static unsigned const  NODES[] = { 7 };
  return  Iterator<unsigned const*>(NODES, NODES+1);
}

Iterator<QIContext const*>  Circuit::getContexts() const {
  static QIContext  ctx("Test", 0, 0);
  return  Iterator<QIContext const*>(&ctx, &ctx+1);
}
