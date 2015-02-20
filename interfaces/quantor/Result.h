#ifndef Q2D_QUANTOR_RESULT_H
#define Q2D_QUANTOR_RESULT_H

extern "C" {
#include "quantor-3.2/quantor.h"
}
#include <cassert>
#include <ostream>

namespace q2d {
namespace quantor {
/**
 * This class provides a thin C++ wrapper around a QuantorResult.
 *
 * @author Thomas B. Preußer <thomas.preusser@utexas.edu>
 */
class Result {
    ::QuantorResult  m_val;

    //- Construction / Destruction
public:
    Result(::QuantorResult  val) : m_val(val) {
        assert((0 <= val) && (val <= 40) && ((val % 10) == 0));
    }
    Result(Result const &o) : m_val(o.m_val) {}
    Result &operator=(Result const &o) {
        m_val = o.m_val;
        return *this;
    }

    ~Result() {}

    //- Utility Operators
public:
    /** True if and only if this Result proved satisfyability. */
    operator bool() const {
        return  m_val == QUANTOR_RESULT_SATISFIABLE;
    }
    /** Conversion to the original detailed ::QuantorResult. */
    operator ::QuantorResult() const {
        return  m_val;
    }
    /** Text representation of the original detailed ::QuantorResult. */
    operator char const* () const;
};

inline std::ostream& operator<<(std::ostream &out, Result  r) {
  out << r.operator char const*();
  return  out;
}
}
}
#endif
