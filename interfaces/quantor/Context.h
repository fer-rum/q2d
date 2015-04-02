#ifndef Q2D_QUANTOR_CONTEXT_H
#define Q2D_QUANTOR_CONTEXT_H

#include <string>
#include "../VariableType.h"

namespace q2d {
namespace quantor {
class Context {
protected:
    Context() {}
    ~Context() {}
public:
    virtual unsigned operator[](std::string const &name) const = 0;
    virtual VariableType typeOf(unsigned  var) const = 0;
};
}
}
#endif
