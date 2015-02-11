#ifndef Q2D_QUANTOR_PARSEEXCEPTION_H
#define Q2D_QUANTOR_PARSEEXCEPTION_H

#include <string>

namespace q2d {
  namespace quantor {
    class QIContext;
    class ParseException {
      std::string const  m_msg;
      QIContext   const &m_ctx;

    public:
      ParseException(std::string  msg, QIContext const &ctx)
	: m_msg(msg), m_ctx(ctx) {}
      ~ParseException() {}

    public:
      std::string const& message() const { return  m_msg; }
      QIContext   const& context() const { return  m_ctx; }
    };
  }
}
#endif
