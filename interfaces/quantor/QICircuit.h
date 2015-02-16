#ifndef QICIRCUIT_H
#define QICIRCUIT_H

#include "Iterator.h"
#include "../Quantor.h"

namespace q2d {
namespace quantor {

class QICircuit {
private:

    QuantorInterface* m_interface;

    // cached variables
    QList<unsigned int> m_configVars;
    QList<unsigned int> m_inputVars;
    QList<unsigned int> m_nodeVars;
public:
    QICircuit(QuantorInterface* interface);

    auto contexts() const
      -> decltype(Iterator<>::over(m_interface->contexts().values())) {
      auto const& ctxs = m_interface->contexts().values();
      return  Iterator<>::over(ctxs);
    }

    /**
     * @brief configVars fetches all configuration variables in all contexts.
     * Excludes input variables
     * @return
     */
    auto configVars() const -> decltype(Iterator<>::over(m_configVars)) {
      return  Iterator<>::over(m_configVars);
    }

    /**
     * @brief nodeVars fetches all node variables in all contexts.
     * Excludes input variables, but includes output vars, since they need no extra handling.
     * @return
     */
    auto nodeVars() const -> decltype(Iterator<>::over(m_nodeVars)) {
      return  Iterator<>::over(m_nodeVars);
    }

    /**
     * @brief inputVars fetches all schematic-wide I/O-port variables
     * @return
     */
    auto inputVars() const -> decltype(Iterator<>::over(m_inputVars)) {
      return  Iterator<>::over(m_inputVars);
    }
};

} // namespace quantor
} // namepsce q2d


#endif // QICIRCUIT_H
