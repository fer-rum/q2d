#line 94 "Quantorizer.ypp"

#include "Quantorizer.hpp"

using namespace q2d::quantor;

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
	if(strncasecmp(formula, "OR", 2) == 0)  res = OR;
	break;
      case 3:
	if     (strncasecmp(formula, "AND", 3) == 0)  res = AND;
	else if(strncasecmp(formula, "XOR", 3) == 0)  res = XOR;
	else if(strncasecmp(formula, "NOR", 3) == 0)  res = NOR;
	else if(strncasecmp(formula, "NOT", 3) == 0)  res = NOT;
	break;
      case 4:
	if     (strncasecmp(formula, "NAND", 4) == 0)  res = NAND;
	else if(strncasecmp(formula, "XNOR", 4) == 0)  res = XNOR;
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

template<typename IT>
void Quantorizer::openScope(QuantorQuantificationType const  type, IT  vars) {
  quantor_scope(quantor, type);
  while(vars) {
    unsigned const  var = *vars++;
    assert(var > 0);
    if(var > max_var)  max_var = var;
    quantor_add(quantor, var);
  }
}

QuantorResult Quantorizer::solve(Circuit const &ctx, std::vector<int> &sol) {
  Quantorizer q;

  // Quantifier Preamble
  q.openScope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE, ctx.getConfigs());
  q.closeScope();
  q.openScope(QUANTOR_UNIVERSAL_VARIABLE_TYPE,   ctx.getInputs());
  q.closeScope();
  q.openScope(QUANTOR_EXISTENTIAL_VARIABLE_TYPE, ctx.getNodes());
  // leave it open!

#ifndef NDEBUG
  q.max_named = q.max_var;
#endif

  { // Parse in Component Specifications
    auto  ctxs = ctx.getContexts();
    while(ctxs)  q.append(*ctxs++);
  }

  q.finish();
  return  q.solve(sol);
}


#line 105 "Quantorizer.cpp"
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

#ifdef TRACE
char const *const  q2d::quantor::Quantorizer::yyterms[] = { "EOF", 
"NOT", "AND", "OR", "XOR", "NAND", "NOR", "XNOR", "IDENT",
"'='", "'('", "')'", };
#endif

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
"   1: [ 0] spec     -> expr '=' expr",
"   2: [ 2] expr     -> expr AND expr",
"   3: [ 2] expr     -> expr OR expr",
"   4: [ 2] expr     -> expr XOR expr",
"   5: [ 2] expr     -> expr NAND expr",
"   6: [ 2] expr     -> expr NOR expr",
"   7: [ 2] expr     -> expr XNOR expr",
"   8: [ 2] expr     -> prim",
"   9: [ 3] prim     -> IDENT",
"  10: [ 0] prim     -> '(' expr ')'",
"  11: [ 1] prim     -> NOT prim",
};
#endif
unsigned short const q2d::quantor::Quantorizer::yylength[] = {
     1,      3,      3,      3,      3,      3,      3,      3,
     1,      1,      3,      2, };
unsigned short const q2d::quantor::Quantorizer::yylhs   [] = {
   (unsigned short)~0u,      0,      1,      1,      1,      1,      1,      1,
     1,      2,      2,      2, };

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
{     -8,      0,     -8,     -8,     -8,     -8,     -8,     -8,      0,     -8,      0,     -8,  },
{      0,      0,      8,      9,     10,     11,     12,     13,      0,     22,      0,      0,  },
{      1,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{     -9,      0,     -9,     -9,     -9,     -9,     -9,     -9,      0,     -9,      0,     -9,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      0,      8,      9,     10,     11,     12,     13,      0,      0,      0,     14,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{    -10,      0,    -10,    -10,    -10,    -10,    -10,    -10,      0,    -10,      0,    -10,  },
{     -7,      0,     -7,     -7,     -7,     -7,     -7,     -7,      0,     -7,      0,     -7,  },
{     -6,      0,     -6,     -6,     -6,     -6,     -6,     -6,      0,     -6,      0,     -6,  },
{     -5,      0,     -5,     -5,     -5,     -5,     -5,     -5,      0,     -5,      0,     -5,  },
{     -4,      0,     -4,     -4,     -4,     -4,     -4,     -4,      0,     -4,      0,     -4,  },
{     -3,      0,     -3,     -3,     -3,     -3,     -3,     -3,      0,     -3,      0,     -3,  },
{     -2,      0,     -2,     -2,     -2,     -2,     -2,     -2,      0,     -2,      0,     -2,  },
{    -11,      0,    -11,    -11,    -11,    -11,    -11,    -11,      0,    -11,      0,    -11,  },
{      0,      4,      0,      0,      0,      0,      0,      0,      5,      0,      6,      0,  },
{     -1,      0,      8,      9,     10,     11,     12,     13,      0,      0,      0,      0,  },
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
      if(yyact == 0)  error("Syntax Error");
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
#line 205 "Quantorizer.ypp"

	    addClause( yystack[yylen - 1], -yystack[yylen - 3]);
	    addClause(-yystack[yylen - 1],  yystack[yylen - 3]);
          
#line 305 "Quantorizer.cpp"
break;
}
case 2: {
#line 209 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
	    addClause(-res,  yystack[yylen - 1]);
	    addClause(-res,  yystack[yylen - 3]);
	    yylval = res;
          
#line 317 "Quantorizer.cpp"
break;
}
case 3: {
#line 216 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause(-res,  yystack[yylen - 1], yystack[yylen - 3]);
	    addClause( res, -yystack[yylen - 1]);
	    addClause( res, -yystack[yylen - 3]);
	    yylval = res;
          
#line 329 "Quantorizer.cpp"
break;
}
case 4: {
#line 223 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
	    addClause(-res,  yystack[yylen - 1],  yystack[yylen - 3]);
	    addClause( res, -yystack[yylen - 1],  yystack[yylen - 3]);
	    addClause( res,  yystack[yylen - 1], -yystack[yylen - 3]);
	    yylval = res;
          
#line 342 "Quantorizer.cpp"
break;
}
case 5: {
#line 231 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause(-res, -yystack[yylen - 1], -yystack[yylen - 3]);
	    addClause( res,  yystack[yylen - 1]);
	    addClause( res,  yystack[yylen - 3]);
	    yylval = res;
          
#line 354 "Quantorizer.cpp"
break;
}
case 6: {
#line 238 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause( res,  yystack[yylen - 1], yystack[yylen - 3]);
	    addClause(-res, -yystack[yylen - 1]);
	    addClause(-res, -yystack[yylen - 3]);
	    yylval = res;
          
#line 366 "Quantorizer.cpp"
break;
}
case 7: {
#line 245 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause( res, -yystack[yylen - 1], -yystack[yylen - 3]);
	    addClause( res,  yystack[yylen - 1],  yystack[yylen - 3]);
	    addClause(-res, -yystack[yylen - 1],  yystack[yylen - 3]);
	    addClause(-res,  yystack[yylen - 1], -yystack[yylen - 3]);
	    yylval = res;
          
#line 379 "Quantorizer.cpp"
break;
}
case 8: {
#line 253 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 385 "Quantorizer.cpp"
break;
}
case 9: {
#line 254 "Quantorizer.ypp"
 yylval = yystack[yylen - 1]; 
#line 391 "Quantorizer.cpp"
break;
}
case 10: {
#line 255 "Quantorizer.ypp"
 yylval = yystack[yylen - 2]; 
#line 397 "Quantorizer.cpp"
break;
}
case 11: {
#line 256 "Quantorizer.ypp"

	    unsigned const  res = makeAuxiliary();
	    addClause( res,  yystack[yylen - 2]);
	    addClause(-res, -yystack[yylen - 2]);
	    yylval = res;
	  
#line 408 "Quantorizer.cpp"
break;
}
        }
        
        yystack.pop(yylen);
        yystack.push(yygoto[*yystack][yylhs[yyrno]], yylval);
      }
    }
  }
}
