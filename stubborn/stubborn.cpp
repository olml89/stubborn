#include "stubborn.h"
#include "Config/configbuilder.h"
#include <QString>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QTimer>

QMessageBox Stubborn::showPermissionToKillPendingProcessMessage()
{
    return QMessageBox(
        QMessageBox::Question,
        "Stubborn",
        QString("%1 is already running. Do you want to terminate it?").arg(this->config.getApplicationPath()),
        QMessageBox::Yes | QMessageBox::No
    );
}

QMessageBox Stubborn::showPermissionToStartCheckingMessage()
{
    QString permissionMessage(
        "Check is running: %1 %2\n"
        "Every: %3 seconds\n"
    );

    return QMessageBox(
        QMessageBox::Question,
        "Stubborn",
        permissionMessage
            .arg(this->config.getApplicationPath())
            .arg(this->config.getArguments())
            .arg(this->config.getInterval()),
        QMessageBox::Yes | QMessageBox::No
    );
}

Stubborn::Stubborn(const QString& configPath)
{
    this->config = ConfigBuilder::build(configPath);
    this->program = Program(this->config.getApplicationPath(), this->config.getArguments());
}

int Stubborn::displayException(const std::exception& e)
{
    return QMessageBox(QMessageBox::Critical, "Stubborn", e.what()).exec();

}

bool Stubborn::start(QApplication& app)
{
    // If the target program is already running, give to the user a chance to terminate it. This way we manually stop
    // target processes running forever if Stubborn is ended somehow, without using the Windows task manager
    /*
    if (this->program.isAlreadyRunning() && this->showPermissionToKillPendingProcessMessage().exec() == QMessageBox::Yes) {
        this->program.stop();
    }

    // Ask the user if he wants to start checking the remote program is up. We don't skip this part even if the target program
    // is already running, to allow exiting from Stubborn altogether after ending the target program
    if (!this->program.isAlreadyRunning()) {

        if (this->showPermissionToStartCheckingMessage().exec() == QMessageBox::No) {
            return false;
        }

        this->program.start();
    }
    */
    //this->program.start();

    // Attach Stubborn to the Windows registry to start with the system, so whenever the computer is rebooted
    // Stubborn starts with it
    QSettings bootUpSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    bootUpSettings.setValue("Stubborn", app.applicationFilePath());
    this->showPermissionToKillPendingProcessMessage().exec();

    // Check the target application is up and running
    QTimer *timer = new QTimer(&app);

    QEventLoop::connect(timer, &QTimer::timeout, [this]() {
        program.keepAwake();
    });

    //timer->start(this->config.getInterval() * 1000);
    return true;
}
