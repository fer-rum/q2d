#ifndef QICIRCUIT_H
#define QICIRCUIT_H

#include "Iterator.h"
#include "QIContext.h"

namespace q2d {
namespace quantor {

class QuantorInterface;

class QICircuit {
private:

    QuantorInterface* m_interface;

    // cached variables
    QList<unsigned int> m_configVars;
    QList<unsigned int> m_inputVars;
    QList<unsigned int> m_nodeVars;
public:
    QICircuit(QuantorInterface* interface);

    Iterator<QIContext> contexts();

    /**
     * @brief configVars fetches all configuration variables in all contexts.
     * Excludes input variables
     * @return
     */
    Iterator<unsigned int> configVars();

    /**
     * @brief nodeVars fetches all node variables in all contexts.
     * Excludes input variables, but includes output vars, since they need no extra handling.
     * @return
     */
    Iterator<unsigned int> nodeVars();

    /**
     * @brief inputVars fetches all schematic-wide I/O-port variables
     * @return
     */
    Iterator<unsigned int> inputVars();
};

} // namespace quantor
} // namepsce q2d


#endif // QICIRCUIT_H