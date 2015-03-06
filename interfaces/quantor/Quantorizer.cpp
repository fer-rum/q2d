#line 70 "Quantorizer.ypp"

#include "Quantorizer.hpp"

#include <cctype>
#include <cassert>
#include <string.h>

extern "C" {
#include "Quantor.h"
}

using namespace q2d::quantor;

//- Life Cycle ---------------------------------------------------------------
Quantorizer::Quantorizer() : max_var(0), context(0), formula(0) {}
Quantorizer::~Quantorizer() {}

//- Parser Interface Methods -------------------------------------------------
inline void Quantorizer::error(std::string  msg) {
  throw  ParseException(msg, 0);
}

unsigned Quantorizer::nextToken(YYSVal &sval) {
  assert(formula != 0);
  while(true) {
    char const  c = *formula++;
    switch(c) {
    case '\0':
      formula = 0;
    case '(':
    case ')':
    case '=':
      return  c;
    case '!':
    case '~':
      return  NOT;
    case '&':
      if(*formula == '&')  formula++;
    case '*':
      return  AND;
    case '|':
      if(*formula == '|')  formula++;
    case '+':
      return  OR;
    case '^':
      return  XOR;
    }
    if(isspace(c))  continue;
    if(isalpha(c) || (c == '_')) {
      char const *p = formula--;
      while(isalnum(*p))  p++;
      unsigned const  len = p-formula;
      unsigned  res = 0;
      switch(len) {
      case 2:
	if(strncmp(formula, "or", 2) == 0)  res = OR;
	break;
      case 3:
	if     (strncmp(formula, "and", 3) == 0)  res = AND;
	else if(strncmp(formula, "xor", 3) == 0)  res = XOR;
	else if(strncmp(formula, "nor", 3) == 0)  res = NOR;
	else if(strncmp(formula, "not", 3) == 0)  res = NOT;
	break;
      case 4:
	if     (strncmp(formula, "nand", 4) == 0)  res = NAND;
	else if(strncmp(formula, "xnor", 4) == 0)  res = XNOR;
	break;
      }
      if(res == 0) {
	unsigned const  var = getVar(std::string(formula, len));
	sval = var;
	res  = VAR;
      }
      formula = p;
      return  res;
    } // isalpha(c)
    error(std::string("Illegal Character: '") + c + "'");
    assert(false);
    return  0;
  }
}

//- Private Parser Helpers ---------------------------------------------------
unsigned Quantorizer::getVar(std::string const &name) {
  Variable const  var = (*context)[name];
  std::map<Variable, unsigned> *cat;
  switch(context->typeOf(var)) {
  case VariableType::CONFIG:  cat = &varConfigs; break;
  case VariableType::INPUT:   cat = &varInputs;  break;
  case VariableType::NODE:    cat = &varNodes;   break;
  default: error("Unknown identifier: " + name);
  }

  // Check if variable is known already
  auto const  v = cat->find(var);
  if(v != cat->end())  return  v->second;

  // Register new variable according to its type
  return (*cat)[var] = ++max_var;
}

inline unsigned Quantorizer::makeAuxiliary() {
  unsigned const  id = ++max_var;
  varAux.push_back(id);
  return  id;
}

inline void Quantorizer::addClause(int const  a) {
  clauses.push_back(a);
  clauses.push_back(0);
}
inline void Quantorizer::addClause(int const  a, int const  b) {
  clauses.push_back(a);
  clauses.push_back(b);
  clauses.push_back(0);
}
inline void Quantorizer::addClause(int const  a, int const  b, int const  c) {
  clauses.push_back(a);
  clauses.push_back(b);
  clauses.push_back(c);
  clauses.push_back(0);
}

//- Public Usage Interface ---------------------------------------------------
void Quantorizer::parse(char const *fct) throw (ParseException) {
  formula = fct;
  try {
    parse();
  }
  catch(ParseException &e) {
    e.position(formula-fct);
    throw;
  }
}

Result Quantorizer::solve(std::vector<unsigned> &sol) {
  q2d::quantor::Quantor         q;      // solver
  std::map<unsigned, Variable>  confs;  // reverse map for configs

  // Problem Building
  q.scope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE);
  for(auto const &e : varConfigs) {
    q.add(e.second);
    confs.emplace(e.second, e.first);
  }
  varConfigs.clear();
  q.add(0);

  q.scope(QUANTOR_UNIVERSAL_VARIABLE_TYPE);
  for(auto const &e : varInputs)  q.add(e.second);
  varInputs.clear();
  q.add(0);

  q.scope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE);
  for(auto const &e : varNodes)  q.add(e.second);
  varNodes.clear();
  for(unsigned  v : varAux)  q.add(v);
  varAux.clear();
  q.add(0);

  for(int  lit : clauses)  q.add(lit);
  clauses.clear();

  // Solve Problem
  Result const  res = q.sat();
  if(res) {
    auto const  end = confs.end();
    for(int const *s = q.assignment(); *s; s++) {
      auto const  it = confs.find(abs(*s));
      if(it != end)  sol.push_back(*s < 0? -it->second : it->second);
    }
  }
  return  res;
}


#line 178 "Quantorizer.cpp"
#include <vector>
class q2d::quantor::Quantorizer::YYStack {
  class Ele {
  public:
    unsigned short  state;
    YYSVal          sval;

  public:
    Ele(unsigned short _state, YYSVal const& _sval)
     : state(_state), sval(_sval) {}
    Ele(unsigned short _state)
     : state(_state) {}
  };
  typedef std::vector<Ele>  Stack;
  Stack  stack;

public:
  YYStack() {}
  ~YYStack() {}

public:
  void push(unsigned short state) {
    stack.push_back(Ele(state));
  }
  void push(unsigned short state, YYSVal const& sval) {
    stack.push_back(Ele(state, sval));
  }
  void pop(unsigned cnt) {
    Stack::iterator  it = stack.end();
    stack.erase(it-cnt, it);
  }

  YYSVal& operator[](unsigned idx) { return  (stack.rbegin()+idx)->sval; }
  unsigned short operator*() const { return  stack.back().state; }
};

char const *const  q2d::quantor::Quantorizer::yyterms[] = { "EOF", 
"NOT", "AND", "OR", "XOR", "NAND", "NOR", "XNOR", "VAR",
"'='", "'('", "')'", };
unsigned short const  q2d::quantor::Quantorizer::yyintern[] = {
     0,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
    10,     11,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,      9,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
   264,    264,    264,    264,    264,    264,    264,    264,
     1,      2,      3,      4,      5,      6,      7,      8,
};

#ifdef TRACE
char const *const  q2d::quantor::Quantorizer::yyrules[] = {
"   0: [ 0] $        -> spec",
"   1: [ 0] spec     -> expr",
"   2: [ 0] spec     -> expr '=' expr",
"   3: [ 2] expr     -> expr AND expr",
"   4: [ 2] expr     -> expr OR expr",
"   5: [ 2] expr     -> expr XOR expr",
"   6: [ 2] expr     -> expr NAND expr",
"   7: [ 2] expr     -> expr NOR expr",
"   8: [ 2] expr     -> expr XNOR expr",
"   9: [ 2] expr     -> prim",
"  10: [ 3] prim     -> VAR",
"  11: [ 0] prim     -> '(' expr ')'",
"  12: [ 1] prim     -> NOT prim",
};
#endif
unsigned short const q2d::quantor::Quantorizer::yylength[] = {
     1,      1,      3,      3,      3,      3,      3,      3,
     3,      1,      1,      3,      2, };
unsigned short const q2d::quantor::Quantorizer::yylhs   [] = {
   (unsigned short)~0u,      0,      0,      1,      1,      1,      1,      1,
     1,      1,      2,      2,      2, };

unsigned short const  q2d::quantor::Quantorizer::yygoto  [][3] = {
{      3,      2,      1,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,     21,  },
{      0,      0,      0,  },
{      0,      7,      1,  },
{      0,      0,      0,  },
{      0,     20,      1,  },
{      0,     19,      1,  },
{      0,     18,      1,  },
{      0,     17,      1,  },
{      0,     16,      1,  },
{      0,     15,      1,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,      0,      0,  },
{      0,     23,      1,  },
{      0,      0,      0,  },
};

signed short const  q2d::quantor::Quantorizer::yyaction[][12] = {
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{     -9,      0,     -9,     -9,     -9,     -9,     -9,     -9,      0,     -9,      0,     -9,  },
{     -1,      0,      8,      9,     10,     11,     12,     13,      0,     22,      0,      0,  },
{      1,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{    -10,      0,    -10,    -10,    -10,    -10,    -10,    -10,      0,    -10,      0,    -10,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      0,      8,      9,     10,     11,     12,     13,      0,      0,      0,     14,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{    -11,      0,    -11,    -11,    -11,    -11,    -11,    -11,      0,    -11,      0,    -11,  },
{     -8,      0,     -8,     -8,     -8,     -8,     -8,     -8,      0,     -8,      0,     -8,  },
{     -7,      0,     -7,     -7,     -7,     -7,     -7,     -7,      0,     -7,      0,     -7,  },
{     -6,      0,     -6,     -6,     -6,     -6,     -6,     -6,      0,     -6,      0,     -6,  },
{     -5,      0,     -5,     -5,     -5,     -5,     -5,     -5,      0,     -5,      0,     -5,  },
{     -4,      0,     -4,     -4,     -4,     -4,     -4,     -4,      0,     -4,      0,     -4,  },
{     -3,      0,     -3,     -3,     -3,     -3,     -3,     -3,      0,     -3,      0,     -3,  },
{    -12,      0,    -12,    -12,    -12,    -12,    -12,    -12,      0,    -12,      0,    -12,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{     -2,      0,      8,      9,     10,     11,     12,     13,      0,      0,      0,      0,  },
};

void q2d::quantor::Quantorizer::parse() {
  YYStack  yystack;
  yystack.push(0);

  // Fetch until error (throw) or accept (return)
  while(true) {
    // Current lookahead
    YYSVal          yysval;
    unsigned short  yytok = nextToken(yysval);

    if(yytok <  YYINTERN)  yytok = yyintern[yytok];
    if(yytok >= YYINTERN)  error("Unknown Token");
#ifdef TRACE
    std::cerr << "Read " << yyterms[yytok] << std::endl;
#endif

    // Reduce until shift
    while(true) {
      signed short const  yyact = yyaction[*yystack][yytok];
      if(yyact == 0) {
        std::string                yymsg("Expecting (");
        signed short const *const  yyrow = yyaction[*yystack];
        for(unsigned  i = 0; i < 12; i++) {
          if(yyrow[i])  yymsg.append(yyterms[i]) += '|';
        }
        *yymsg.rbegin() = ')';
        error(yymsg.append(" instead of ").append(yyterms[yytok]));
        return;
      }
      if(yyact >  1) { // shift
#ifdef TRACE
        std::cerr << "Push " << yyterms[yytok] << std::endl;
#endif
        yystack.push(yyact, yysval);
        break;
      }
      else {           // reduce (includes accept)
        YYSVal                yylval;
        unsigned short const  yyrno = (yyact < 0)? -yyact : 0;
        unsigned short const  yylen = yylength[yyrno];
        
#ifdef TRACE
        std::cerr << "Reduce by " << yyrules[yyrno] << std::endl;
#endif
        switch(yyrno) { // do semantic actions
        case 0:         // accept
          return;
case 1: {
#line 254 "Quantorizer.ypp"

        addClause(yystack[yylen - 1]);
       
#line 384 "Quantorizer.cpp"
break;
}
case 2: {
#line 257 "Quantorizer.ypp"

        addClause( yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-yystack[yylen - 1],  yystack[yylen - 3]);
       
#line 393 "Quantorizer.cpp"
break;
}
case 3: {
#line 261 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1]);
        addClause(-res,  yystack[yylen - 3]);
        yylval = res;
       
#line 405 "Quantorizer.cpp"
break;
}
case 4: {
#line 268 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res,  yystack[yylen - 1], yystack[yylen - 3]);
        addClause( res, -yystack[yylen - 1]);
        addClause( res, -yystack[yylen - 3]);
        yylval = res;
       
#line 417 "Quantorizer.cpp"
break;
}
case 5: {
#line 275 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1],  yystack[yylen - 3]);
        addClause( res, -yystack[yylen - 1],  yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1], -yystack[yylen - 3]);
        yylval = res;
       
#line 430 "Quantorizer.cpp"
break;
}
case 6: {
#line 283 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1]);
        addClause( res,  yystack[yylen - 3]);
        yylval = res;
       
#line 442 "Quantorizer.cpp"
break;
}
case 7: {
#line 290 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res,  yystack[yylen - 1], yystack[yylen - 3]);
        addClause(-res, -yystack[yylen - 1]);
        addClause(-res, -yystack[yylen - 3]);
        yylval = res;
       
#line 454 "Quantorizer.cpp"
break;
}
case 8: {
#line 297 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1],  yystack[yylen - 3]);
        addClause(-res, -yystack[yylen - 1],  yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1], -yystack[yylen - 3]);
        yylval = res;
       
#line 467 "Quantorizer.cpp"
break;
}
case 9: {
#line 305 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 473 "Quantorizer.cpp"
break;
}
case 10: {
#line 307 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 479 "Quantorizer.cpp"
break;
}
case 11: {
#line 308 "Quantorizer.ypp"
 yylval = yystack[yylen - 2]; 
#line 485 "Quantorizer.cpp"
break;
}
case 12: {
#line 309 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res,  yystack[yylen - 2]);
        addClause(-res, -yystack[yylen - 2]);
        yylval = res;
       
#line 496 "Quantorizer.cpp"
break;
}
        }
        
        yystack.pop(yylen);
        yystack.push(yygoto[*yystack][yylhs[yyrno]], yylval);
      }
    }
  }
}
