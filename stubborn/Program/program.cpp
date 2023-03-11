#include "program.h"
#include "File/file.h"
#include <QFileInfo>
#include <QProcess>

bool Program::isValidProgram(const QString& applicationPath)
{
    // https://stackoverflow.com/questions/2863683/how-to-find-if-a-file-is-an-exe
    // https://stackoverflow.com/a/2863740
    return File::getContent(applicationPath).left(2) == "MZ";
}

Program::Program() {}

Program::Program(const QString& applicationPath, const QString& arguments)
{
    this->applicationInfo = QFileInfo(applicationPath);
    this->arguments = arguments.split(" ");
    this->process = Process(this->applicationInfo);
}

bool Program::isAlreadyRunning()
{
    return this->process.isRunning();
}

void Program::start()
{
    QProcess::startDetached(this->applicationInfo.absoluteFilePath(), this->arguments);
    this->process = Process(this->applicationInfo);
}

void Program::keepAwake()
{
    if (this->isAlreadyRunning()) {
        qDebug() << this->applicationInfo.absoluteFilePath() + "already running";
        return;
    }

    qDebug() << "starting" << this->applicationInfo.absoluteFilePath();

    //QStringList arguments;
    //arguments << "--algo" << "ethash" << "--server" << "eu1.ethermine.org" << "--port" << "4444" << "--user" << "0x3917e20e0867dac01E7D80abC2386F815F5bbd02.Laptop";

    //QProcess process;
    //process.startDetached(this->applicationInfo.absoluteFilePath(), arguments);
    //QProcess *process = new QProcess();
    //process->start(this->applicationInfo.absoluteFilePath(), arguments);
    //delete process;

    //this->start();
}

void Program::stop()
{
    // Prevent multiple instances being running
    while (this->process.isRunning()) {
        this->process.kill();
        this->process = Process(this->applicationInfo);
    }
}

