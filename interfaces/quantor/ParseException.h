#ifndef Q2D_QUANTOR_PARSEEXCEPTION_H
#define Q2D_QUANTOR_PARSEEXCEPTION_H

#include <string>

namespace q2d {
namespace quantor {
/**
 * This class captures information about and the location of
 * a parsing problem encountered by the Quantorizer and may
 * be thrown by Quantorizer::solve().
 *
 * @author Thomas B. Preußer <thomas.preusser@utexas.edu>
 */
class ParseException {
    std::string const  m_msg;
    unsigned           m_pos;

public:
    ParseException(std::string  msg, unsigned  pos)
        : m_msg(msg), m_pos(pos) {}
    ~ParseException() {}

public:
    std::string const &message() const {
        return  m_msg;
    }
    unsigned position() const {
        return  m_pos;
    }
    void position(unsigned  pos) {
	m_pos = pos;
    }
};
}
}
#endif
