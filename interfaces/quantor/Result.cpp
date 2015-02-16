#include "Result.h"

using namespace q2d::quantor;

Result::operator char const*() const {
  static char const *const  TEXTS[] = {
    "UNKNOWN", "SAT", "UNSAT", "TIMEOUT", "SPACEOUT"
  };
  unsigned const  r = m_val/10;
  return  TEXTS[r>4? 0 : r];
}
