#include "ConsoleLogger.h"
#include "LogEntry.h"
#include "Logger.h"
#include "LogLevel.h"
#include "LogManager.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace q2d::logging;
using namespace std;

ConsoleLogger::ConsoleLogger(QObject* parent)
    : LoggerListener(parent)
{}

void
ConsoleLogger::handleEntry(LogEntry* newEntry, Logger* sender){

    QString levelName = newEntry->logLevel()->name();
    QString message = newEntry->message();

    chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(
                                  newEntry->timestamp() - sender->manager()->startTime());

    /*
     * HACK: Converting to system_clock via the offsets
     * to then convert to time_t, which in turn can be printed later.
     */
//    time_t time = chrono::system_clock::to_time_t(
//                      chrono::system_clock::now()
//                      + (newEntry->timestamp() - chrono::steady_clock::now()));
//    string timeString = ctime(&time);
//    timeString.resize(timeString.size() - 1); // cut the newline


    /*
     * Wanted to use put_time() here, but it is only available from gcc 5 on.
     * Maybe at a later point in time this might be upgraded.
     */
    cout << "[" << setfill('0') << setw(4) << us.count() / 1000000 << "."
         << setw(6) << us.count() % 1000000 << " sec] ("
         << setfill(' ') << setw(10) << sender->objectName().toStdString() << ") "
         << setw(8) << levelName.toStdString() << " : "
         << message.toStdString() << endl;
}
