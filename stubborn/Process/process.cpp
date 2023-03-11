#include "process.h"
#include <psapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <QFileInfo>
#include <QString>

Process::Process() {}

Process::Process(const QFileInfo& programInfo)
{
    // https://stackoverflow.com/questions/51608767/unable-to-convert-qstring-to-tchar-after-removing-unicode-def
    // https://stackoverflow.com/a/51617885
    const WCHAR* const executableName = (const WCHAR*)programInfo.fileName().utf16();
    const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return;
    }

    do {
        // The name of our executable file is the same as an existing running process. We have to check if the file from where the
        // process was launched is the same as our executable file, to prevent the function returning false positives in the case
        // of two executables named equal
        if (!_tcsicmp(entry.szExeFile, executableName) && Process(entry.th32ProcessID).getFilePath() == programInfo.absoluteFilePath()) {
            this->PID = entry.th32ProcessID;
            CloseHandle(snapshot);
            return;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
}

Process::Process(DWORD PID)
{
    this->PID = PID;
}

bool Process::isRunning()
{
    return this->PID != 0;
}

QString Process::getFilePath()
{
    const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->PID);
    WCHAR processPath[MAX_PATH];

    if (K32GetModuleFileNameExW(hProcess, NULL, processPath, _countof(processPath)) == 0) {
        CloseHandle(hProcess);
        return QString();
    }

    CloseHandle(hProcess);
    return QFileInfo(QString::fromWCharArray(processPath)).absoluteFilePath();
}

void Process::kill()
{
    const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->PID);
    TerminateProcess(hProcess, 1);
    CloseHandle(hProcess);
    this->PID = 0;
}
