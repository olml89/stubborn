#include "file.h"
#include "qdebug.h"
#include <exception>
#include <QString>
#include <QByteArray>
#include <QFile>

QByteArray File::getContent(const QString& filePath)
{
    qDebug() << filePath;
    if (!QFile::exists(filePath)) {
        throw std::runtime_error(QString("The file '%1' does not exist").arg(filePath).toStdString());
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(QString("The file '%1' can't be opened to be read").arg(filePath).toStdString());
    }

    QByteArray content = file.readAll();
    file.close();
    return content;
}
