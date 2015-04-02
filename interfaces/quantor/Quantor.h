#ifndef Q2D_QUANTOR_QUANTOR_H
#define Q2D_QUANTOR_QUANTOR_H

#define TRACE
#ifdef TRACE
#include <iostream>
#endif

extern "C" {
#include "quantor-3.2/quantor.h"
}

#include "Result.h"



namespace q2d {
namespace quantor {
/**
 * This class provides a thin C++ wrapper around the quantor C-library.
 *
 * @author Thomas B. Preußer <thomas.preusser@utexas.edu>
 */
class Quantor {
    ::Quantor* const  quantor;

    //- Construction / Destruction
public:
    Quantor() : quantor(quantor_new()) {}
    ~Quantor() {
        quantor_delete(quantor);
    }

    //- Information
public:
    char const* id()        const {
        return  quantor_id();
    }
    char const* copyright() const {
        return  quantor_copyright();
    }
    char const* version()   const {
        return  quantor_version();
    }

    //- Problem Construction
public:
    char const* scope(::QuantorQuantificationType const  quant) {
#ifdef TRACE
        std::cerr << "S " << (int)quant << std::endl;
#endif
        return  quantor_scope(quantor, quant);
    }
    char const* add(int const  lit) {
#ifdef TRACE
        std::cerr << lit << (lit? ", " : "\n");
#endif
        return  quantor_add(quantor, lit);
    }

    //- Solving / Result Retrieval
public:
    Result     sat()         {
#ifdef TRACE
        std::cerr << "\nD" << std::endl;
#endif
        return  quantor_sat(quantor);
    }
    int const* assignment() const {
        return  quantor_assignment(quantor);
    }
};
}
}

#endif
