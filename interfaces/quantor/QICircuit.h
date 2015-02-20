#ifndef Q2D_QUANTOR_QICIRCUIT_H
#define Q2D_QUANTOR_QICIRCUIT_H

#include <QVector>
#include "../Quantor.h"

namespace q2d {
namespace quantor {

class QICircuit {
private:

    QuantorInterface const &m_interface;

    // cached variables
    QVector<unsigned int> m_configVars;
    QVector<unsigned int> m_inputVars;
    QVector<unsigned int> m_nodeVars;

public:
    QICircuit(QuantorInterface const &interface);

    auto contexts() const -> decltype(m_interface.contexts()) {
        return  m_interface.contexts();
    }

    /**
     * @brief configVars fetches all configuration variables in all contexts.
     * Excludes input variables
     * @return
     */
    QVector<unsigned> const &configVars() const {
        return  m_configVars;
    }

    /**
     * @brief nodeVars fetches all node variables in all contexts.
     * Excludes input variables, but includes output vars, since they need no extra handling.
     * @return
     */
    QVector<unsigned> const &nodeVars() const {
        return  m_nodeVars;
    }

    /**
     * @brief inputVars fetches all schematic-wide I/O-port variables
     * @return
     */
    QVector<unsigned> const &inputVars() const {
        return  m_inputVars;
    }
};

} // namespace quantor
} // namepsce q2d

#endif // Q2D_QUANTOR_QICIRCUIT_H
