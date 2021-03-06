#ifndef Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
#define Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
#line 1 "Quantorizer.ypp"

#include <vector>
#include <map>

#include "Context.h"
#include "ParseException.h"
#include "Result.h"

namespace q2d {
  namespace quantor {
    class SVal;
  }
}

#line 18 "Quantorizer.hpp"
#include <string>
namespace q2d {
namespace quantor {
class Quantorizer {
  typedef SVal YYSVal;
  class YYStack;
#line 26 "Quantorizer.ypp"

  // Variable Bookkeeping
  unsigned  max_var;

  typedef unsigned Variable;
  std::map<Variable, unsigned>  varConfigs;
  std::map<Variable, unsigned>  varInputs;
  std::map<Variable, unsigned>  varNodes;

  std::vector<unsigned>  varAux;
  std::vector<int>       clauses;

  // Current Parsing State
  Context const *context;
  char    const *formula;

//- Life Cycle ---------------------------------------------------------------
public:
  Quantorizer();
  ~Quantorizer();

//- Parser Interface Methods -------------------------------------------------
private:
  void error(std::string  msg);
  unsigned nextToken(YYSVal &sval);

//- Private Parser Helpers ---------------------------------------------------
private:
  unsigned getVar(std::string const &name);
  unsigned makeAuxiliary();
  void addClause(SVal const &clause);
  void addClause(int const  a);
  void addClause(int const  a, int const  b);
  void addClause(int const  a, int const  b, int const  c);

//- Usage Interface ----------------------------------------------------------
public:
  // Builds a problem by adding contexts with formulae.
  void set(Context const &ctx) {
    context = &ctx;
  }
  void parse(char const *fct) throw (ParseException);

  // Solves the current problem and clears this Quantorizers state.
  Result solve(std::vector<int> &sol);

#line 72 "Quantorizer.hpp"
private:
  void parse();
public:
enum {
  NOT = 256,
  AND = 257,
  OR = 258,
  XOR = 259,
  NAND = 260,
  NOR = 261,
  XNOR = 262,
  VAR = 263,
};
private:
enum { YYINTERN = 264 };
static unsigned short const  yyintern[];
static char const    *const  yyterms[];

private:
static unsigned short const  yylength[];
static unsigned short const  yylhs   [];
static char const    *const  yyrules [];

private:
static unsigned short const  yygoto  [][4];
static signed   short const  yyaction[][15];
};
}}
#endif
