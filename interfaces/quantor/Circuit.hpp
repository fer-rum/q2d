#ifndef __CIRCUIT_HPP
#define __CIRCUIT_HPP

#include "Iterator.h"

namespace q2d {
  namespace quantor {
    class QIContext;
    class Circuit {
    public:
      Iterator<unsigned  const*> getConfigs()  const;
      Iterator<unsigned  const*> getInputs()   const;
      Iterator<unsigned  const*> getNodes()    const;
      Iterator<QIContext const*> getContexts() const;
    };
  }
}
#endif
