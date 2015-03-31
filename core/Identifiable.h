#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include <QString>

namespace q2d {
namespace core {

/**
 * @brief The Identifiable interface abstracts all things that carry an ID.
 * An identifieable contains a local ID and a parent.
 * A full ID can be derived by recursively appending local ID to the parents full ID.
 * If no parent is present, the full ID equals the local ID.
 *
 * The interface also offers methods to check the validity of a given ID.
 */
class Identifiable {
private:
    Identifiable* m_parent;
    QString m_localId;
public:
    Identifiable(QString localId, Identifiable* parent = nullptr);

    QString localId() const;
    QString fullId() const;

    /**
     * @brief isValidLocalId checks, if a given ID is valid to be used as a local ID.
     * The rules are the same as the ones for a full ID and additionally the ID must not contain the
     * HIERARCHY_SEPERATOR character.
     *
     * @param id is the ID which should be checked for validity.
     * @return true, if the ID can be used as a local ID; Otherwise false.
     */
    static bool isValidLocalId(const QString id);

    // TODO more criteria
    /**
     * @brief isValidFullId checks, if a given ID is valid to be used as a full ID.
     * The following criteria must be fulfilled:
     * <ul>
     *  <li>the ID must not be empty</li>
     *  <li>the ID may not contain whitespaces</li>
     *  <li>the ID may not begin with a number</li>
     * </ul>
     *
     * @param id is the ID which should be checked for validity.
     * @return true, if the ID can be used as a local ID; Otherwise false.
     */
    static bool isValidFullId(const QString id);
};

} // namespace core
} // namespace q2d

#endif // IDENTIFIABLE_H
