#line 67 "Quantorizer.ypp"

#include "Quantorizer.hpp"

using namespace q2d::quantor;

//- Life Cycle ---------------------------------------------------------------
inline Quantorizer::Quantorizer() : max_var(0), context(0), formula(0) {}
inline Quantorizer::~Quantorizer() {}

//- Problem Building ---------------------------------------------------------
template<typename IT>
void Quantorizer::openScope(QuantorQuantificationType const  type, IT  vars) {
  quantor.scope(type);
  for(unsigned const  var : vars) {
    assert(var > 0);
    if(var > max_var)  max_var = var;
    quantor.add(var);
  }
}
inline void Quantorizer::closeScope() { quantor.add(0); }

//- Private Parser Helpers ---------------------------------------------------
inline unsigned Quantorizer::makeAuxiliary() {
  unsigned const  res = ++max_var;
  quantor.add(res);
  return  res;
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

//- Parser Interface Methods -------------------------------------------------
inline void Quantorizer::error(std::string  msg) {
  throw  ParseException(msg, *context);
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
    unsigned const  var = (*context)[std::string(formula, len)];
    assert(var > 0);
    assert(var <= max_named);
    sval = var;
    res  = IDENT;
      }
      formula = p;
      return  res;
    } // isalpha(c)
    error(std::string("Illegal Character: '") + c + "'");
    assert(false);
    return  0;
  }
}

//- Public Usage Interface ---------------------------------------------------
inline Result Quantorizer::solve0(QICircuit const &c, std::vector<int> &sol) {
  // Quantifier Preamble
  openScope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE, c.configVars());
  closeScope();
  openScope(QUANTOR_UNIVERSAL_VARIABLE_TYPE,   c.inputVars());
  closeScope();
  openScope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE, c.nodeVars());
  // leave it open!
#ifndef NDEBUG
  max_named = max_var;
#endif

  // Parse in Component Specifications
  for(QIContext const &ctx : c.contexts()) {
    context = &ctx;
    for(std::string const&  f : ctx.functions()) {
      formula = f.c_str();
      parse();
    }
  }

  // Finish Problem Specification
  closeScope();
  for(int  lit : clauses)  quantor.add(lit);

  // Solve Problem
  Result const  res = quantor.sat();
  if(res == QUANTOR_RESULT_SATISFIABLE) {
    int const *s = quantor.assignment();
    while(*s)  sol.push_back(*s++);
  }
  return  res;
}

Result Quantorizer::solve(QICircuit const &c, std::vector<int> &sol) {
  return  Quantorizer().solve0(c, sol);
}


#line 148 "Quantorizer.cpp"
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
"NOT", "AND", "OR", "XOR", "NAND", "NOR", "XNOR", "IDENT",
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
"  10: [ 3] prim     -> IDENT",
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
case 2: {
#line 221 "Quantorizer.ypp"

        addClause( yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-yystack[yylen - 1],  yystack[yylen - 3]);
          
#line 355 "Quantorizer.cpp"
break;
}
case 3: {
#line 225 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1]);
        addClause(-res,  yystack[yylen - 3]);
        yylval = res;
          
#line 367 "Quantorizer.cpp"
break;
}
case 4: {
#line 232 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res,  yystack[yylen - 1], yystack[yylen - 3]);
        addClause( res, -yystack[yylen - 1]);
        addClause( res, -yystack[yylen - 3]);
        yylval = res;
          
#line 379 "Quantorizer.cpp"
break;
}
case 5: {
#line 239 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1],  yystack[yylen - 3]);
        addClause( res, -yystack[yylen - 1],  yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1], -yystack[yylen - 3]);
        yylval = res;
          
#line 392 "Quantorizer.cpp"
break;
}
case 6: {
#line 247 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1]);
        addClause( res,  yystack[yylen - 3]);
        yylval = res;
          
#line 404 "Quantorizer.cpp"
break;
}
case 7: {
#line 254 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res,  yystack[yylen - 1], yystack[yylen - 3]);
        addClause(-res, -yystack[yylen - 1]);
        addClause(-res, -yystack[yylen - 3]);
        yylval = res;
          
#line 416 "Quantorizer.cpp"
break;
}
case 8: {
#line 261 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
        addClause( res,  yystack[yylen - 1],  yystack[yylen - 3]);
        addClause(-res, -yystack[yylen - 1],  yystack[yylen - 3]);
        addClause(-res,  yystack[yylen - 1], -yystack[yylen - 3]);
        yylval = res;
          
#line 429 "Quantorizer.cpp"
break;
}
case 9: {
#line 269 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 435 "Quantorizer.cpp"
break;
}
case 10: {
#line 270 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 441 "Quantorizer.cpp"
break;
}
case 11: {
#line 271 "Quantorizer.ypp"
 yylval = yystack[yylen - 2]; 
#line 447 "Quantorizer.cpp"
break;
}
case 12: {
#line 272 "Quantorizer.ypp"

        unsigned const  res = makeAuxiliary();
        addClause( res,  yystack[yylen - 2]);
        addClause(-res, -yystack[yylen - 2]);
        yylval = res;
      
#line 458 "Quantorizer.cpp"
break;
}
        }
        
        yystack.pop(yylen);
        yystack.push(yygoto[*yystack][yylhs[yyrno]], yylval);
      }
    }
  }
}
