#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QByteArray>

class File
{
    public:
        static QByteArray getContent(const QString& filePath);
};

#endif // FILE_H
