#ifndef UTIL_H
#define UTIL_H

#include <QString>

namespace q2d {

/**
 * This namespace contains utility functions that fit nowhere else.
 */
namespace util {

QString ptrToString(const void* ptr);

QString intToString(const int value, const int padding = 0);

} // namespace util
} // namespace q2d

#endif // UTIL_H
