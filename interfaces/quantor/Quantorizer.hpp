#ifndef Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
#define Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
#line 1 "Quantorizer.ypp"

#include <vector>
#include <cctype>
#include <cassert>

#include <strings.h>

#include "Quantor.h"
#include "QICircuit.h"
#include "QIContext.h"
#include "ParseException.h"

 using namespace q2d::quantor;

#line 18 "Quantorizer.hpp"
#include <string>
namespace q2d {
namespace quantor {
class Quantorizer {
  typedef unsigned YYSVal;
  class YYStack;
#line 26 "Quantorizer.ypp"

  Quantor   quantor;
  unsigned  max_var;
#ifndef NDEBUG
  unsigned  max_named;
#endif

  std::vector<int>  clauses;
  QIContext const  *context;
  char      const  *formula;

//- Life Cycle ---------------------------------------------------------------
private:
  Quantorizer();
  ~Quantorizer();

//- Problem Building ---------------------------------------------------------
private:
  template<typename IT>
  void openScope(QuantorQuantificationType const  type, IT  vars);
  void closeScope();

//- Private Parser Helpers ---------------------------------------------------
private:
  unsigned makeAuxiliary();
  void addClause(int const  a, int const  b);
  void addClause(int const  a, int const  b, int const  c);

//- Parser Interface Methods -------------------------------------------------
private:
  void error(std::string  msg);
  unsigned nextToken(YYSVal &sval);

//- Usage Interface ----------------------------------------------------------
private:
  Result solve0(QICircuit const &c, std::vector<int> &sol);
public:
  static Result solve(QICircuit const &c, std::vector<int> &sol);

#line 65 "Quantorizer.hpp"
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
  IDENT = 263,
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
static unsigned short const  yygoto  [][3];
static signed   short const  yyaction[][12];
};
}}
#endif
