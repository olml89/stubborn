#ifndef PROGRAM_H
#define PROGRAM_H

#include "Process/process.h"
#include <QFileInfo>
#include <QStringList>
#include <QString>
#include <QDateTime>

class Program
{
    private:
        QFileInfo applicationInfo;
        QStringList arguments;
        Process process;

    public:
        static bool isValidProgram(const QString& applicationPath);
        Program();
        Program(const QString& applicationPath, const QString& arguments);
        bool isAlreadyRunning();
        void start();
        void keepAwake();
        void stop();
};

#endif // PROGRAM_H
