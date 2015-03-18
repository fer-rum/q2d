#include "Quantorizer.hpp"

#include <iostream>

#include <string>
#include <vector>
#include <map>

using namespace q2d::quantor;

class MyContext : public Context {
  std::map<std::string, unsigned>  name2id;
  std::vector<std::string>         id2name;

public:
  MyContext() {}
  ~MyContext() {}

public:
  unsigned operator[](std::string const &name) const override;
  VariableType typeOf(unsigned var) const override;

public:
  std::string const &nameOf(unsigned var) const;
};

unsigned MyContext::operator[](std::string const &name) const {
  {
    auto const  it = name2id.find(name);
    if(it != name2id.end())  return  it->second;
  }
  {
    unsigned const  id = id2name.size();
    const_cast<std::remove_const<decltype(id2name)>::type&>(id2name).push_back(name);
    const_cast<std::remove_const<decltype(name2id)>::type&>(name2id)[name] = id;
    return  id;
  }
}

VariableType MyContext::typeOf(unsigned var) const {
  if(var < id2name.size()) {
    switch(id2name[var][0]) {
    case 'x':  return  VariableType::INPUT;
    case 'c':  return  VariableType::CONFIG;
    default:   return  VariableType::NODE;
    }
  }
  return  VariableType::INVALID;
}

std::string const  UNDEF("<undef>");
std::string const &MyContext::nameOf(unsigned var) const {
  return  var < id2name.size()? id2name[var] : UNDEF;
}

int main(int const  argc, char const *const  argv[]) {
  Quantorizer  q;

  // Parse Specification
  MyContext const  ctx;
  q.set(ctx);
  for(int  i = 1; i < argc; i++) {
    try {
      q.parse(argv[i]);
    }
    catch(ParseException const &e) {
      std::cerr << "ParseException in \"" << argv[i] << "\" @" << e.position()
		<< ": " << e.message() << std::endl;
      return 1;
    }
  }

  // Compute Solution
  std::vector<int>  sol;
  Result const  res = q.solve(sol);

  std::cout << res << std::endl;
  if(res) {
    for(int const  v : sol) {
      std::cout << (v < 0? '-' : ' ') << ctx.nameOf(abs(v)) << std::endl;
    }
  }
}
