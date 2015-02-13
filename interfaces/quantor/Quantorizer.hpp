#ifndef Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
#define Q2D_QUANTOR_QUANTORIZER_HPP_INCLUDED
// #line 1 "Quantorizer.ypp"

extern "C" {
#include "quantor-3.2/quantor.h"
#include <strings.h>
}
#include <vector>
#include <cctype>
#include <cassert>
#include "Circuit.hpp"
#include "QIContext.h"
#include "ParseException.h"

// #line 16 "Quantorizer.hpp"
#include <string>
namespace q2d {
namespace quantor {

class Quantorizer {
  typedef unsigned YYSVal;
  class YYStack;
// #line 24 "Quantorizer.ypp"

  Quantor *const  quantor;
  unsigned        max_var;
#ifndef NDEBUG
  unsigned        max_named;
#endif

  std::vector<int>  clauses;
  QIContext const  *context;
  char      const  *formula;

//- Life Cycle ---------------------------------------------------------------
private:
  Quantorizer()
    : quantor(quantor_new()), max_var(0), context(0), formula(0) {}
  ~Quantorizer() {
    quantor_delete(quantor);
  }

//- Problem Building ---------------------------------------------------------
  template<typename IT>
  void openScope(QuantorQuantificationType const  type, IT  vars);
  void closeScope() { quantor_add(quantor, 0); }

  void append(QIContext const &ctx) {
    context = &ctx;
    Iterator<QList<std::string>::const_iterator>  formulas = ctx.functionIterator();
    while(formulas) {
      formula = formulas++->c_str();
      parse();
    }
  }

  void finish() {
    // Finish Problem Specification
    closeScope();
    for(int  lit : clauses)  quantor_add(quantor, lit);
  }

  QuantorResult solve(std::vector<int> &sol) {
    QuantorResult const  res = quantor_sat(quantor);
    if(res == QUANTOR_RESULT_SATISFIABLE) {
      int const *s = quantor_assignment(quantor);
      while(*s)  sol.push_back(*s++);
    }
    return  res;
  }

//- Public Usage Interface ---------------------------------------------------
public:
  static QuantorResult solve(QICircuit& ctx, std::vector<int> &sol);
  static char const* resultText(QuantorResult const  res);

//- Parser Interface Methods -------------------------------------------------
private:
  unsigned nextToken(YYSVal &sval);
  void error(std::string  msg) {
    throw  ParseException(msg, *context);
  }

//- Custom Parser Helpers ----------------------------------------------------
private:
  unsigned makeAuxiliary() {
    unsigned const  res = ++max_var;
    quantor_add(quantor, res);
    return  res;
  }
  void addClause(int const  a, int const  b) {
    clauses.push_back(a);
    clauses.push_back(b);
    clauses.push_back(0);
  }
  void addClause(int const  a, int const  b, int const  c) {
    clauses.push_back(a);
    clauses.push_back(b);
    clauses.push_back(c);
    clauses.push_back(0);
  }

// #line 103 "Quantorizer.hpp"
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
