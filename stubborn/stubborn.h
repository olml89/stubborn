#ifndef STUBBORN_H
#define STUBBORN_H

#include "Config/config.h"
#include "Program/program.h"
#include <QMessageBox>
#include <QString>
#include <QApplication>

class Stubborn
{
    private:
        Config config;
        Program program;
        QMessageBox showPermissionToKillPendingProcessMessage();
        QMessageBox showPermissionToStartCheckingMessage();

    public:
        static int displayException(const std::exception& e);
        Stubborn(const QString& configPath);
        bool start(QApplication& app);

};

#endif // STUBBORN_H
