#include "Util.h"


QString
q2d::util::ptrToString(const void* ptr) {
    // It will use the correct size and type for pointers (quintptr and QT_POINTER_SIZE) and will always prefix "0x"
    // To prefix the value with zeros, the fourth parameter needs to be ´QChar('0')´.
    // To output the correct number of digits, QT_POINTER_SIZE needs to be doubled (because each byte needs 2 hex digits).
    return QString("0x%1").arg((quintptr)ptr, QT_POINTER_SIZE * 2, 16, QChar('0'));
}

QString
q2d::util::intToString(const int value, const int padding) {

    return QString("%1").arg(QString::number(value), padding, QChar('0'));
}
