#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>
#include <QString>

class Config
{
    private:
        QString applicationPath;
        int interval;
        QString arguments;

    public:
        Config();
        Config(const QJsonObject& configObject);
        const QString& getApplicationPath();
        int getInterval();
        const QString& getArguments();
};

#endif // CONFIG_H
