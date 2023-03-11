#ifndef PROCESS_H
#define PROCESS_H

#include <QFileInfo>
#include <QString>
#include "windows.h"

class Process
{
    private:
        DWORD PID = 0;

    public:
        //static DWORD getPID(const QFileInfo& programInfo);
        static Process run();
        Process();
        Process(const QFileInfo& programInfo);
        Process(DWORD PID);
        bool isRunning();
        QString getFilePath();
        void kill();
};

#endif // PROCESS_H
