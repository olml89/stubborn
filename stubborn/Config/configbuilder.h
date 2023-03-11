#ifndef CONFIGBUILDER_H
#define CONFIGBUILDER_H

#include "Config/config.h"
#include <QString>
#include <QJsonObject>

class ConfigBuilder
{
    public:
        static Config build(const QString& configPath);
};

#endif // CONFIGBUILDER_H
