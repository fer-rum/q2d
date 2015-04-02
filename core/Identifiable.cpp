
#include "../Constants.h"
#include "Identifiable.h"

#include <QRegularExpression>

using namespace q2d::constants;
using namespace q2d::core;

Identifiable::Identifiable(QString localId, Identifiable* parent) {
    Q_ASSERT(isValidLocalId(localId));
    m_parent = parent;
    m_localId = localId;
}

QString
Identifiable::localId() const {
    return m_localId;
}

QString
Identifiable::fullId() const {
    if(m_parent == nullptr){
        return m_localId;
    } else {
        return m_parent->fullId() + HIERARCHY_SEPERATOR + m_localId;
    }
}

bool
Identifiable::isValidLocalId(const QString id) {
    if(!isValidFullId(id)){ return false; }
    if(id.contains(HIERARCHY_SEPERATOR)){ return false; }

    return true;
}

bool
Identifiable::isValidFullId(const QString id) {
    if(id.isEmpty()){ return false; }
    if(id.contains(QRegularExpression("\\s"))){ return false; } // no whitespaces
    if(id.contains(QRegularExpression("^\\d"))){ return false; } // may not begin with number

    return true;
}
