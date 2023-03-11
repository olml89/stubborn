#include "config.h"

Config::Config() {}

Config::Config(const QJsonObject& configObject)
{
    this->applicationPath = configObject.value("application").toString();
    this->interval = configObject.value("interval").toInt();

    if (configObject.contains("arguments")) {
        this->arguments = configObject.value("arguments").toString();
    }
}

const QString& Config::getApplicationPath()
{
    return this->applicationPath;
}

int Config::getInterval()
{
    return this->interval;
}

const QString& Config::getArguments()
{
    return this->arguments;
}
