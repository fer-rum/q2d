#ifndef Q2D_QUANTOR_RESULT_H
#define Q2D_QUANTOR_RESULT_H

extern "C" {
#include "quantor-3.2/quantor.h"
}
#include <cassert>

namespace q2d {
  namespace quantor {
    /**
     * This class provides a thin C++ wrapper around a QuantorResult.
     *
     * @author Thomas B. Preußer <thomas.preusser@utexas.edu>
     */
    class Result {
      QuantorResult const  m_val;

      //- Construction / Destruction
    public:
      Result(QuantorResult const &val) : m_val(val) {
    assert((0 <= val) && (val <= 40) && ((val%10) == 0));
      }
      ~Result() {}

      //- Utility
    public:
      operator ::QuantorResult() const { return  m_val; }
      operator char const*() const;
    };
  }
}
#endif
