#include "Config/configbuilder.h"
#include "Config/config.h"
#include "File/file.h"
#include "Program/program.h"
#include <exception>
#include <QFile>
#include <QJsonDocument>

Config ConfigBuilder::build(const QString& configPath)
{
    // Check the specified config file exists, can be opened and contains a valid JSON object
    QJsonDocument jsonConfig = QJsonDocument::fromJson(File::getContent(configPath));

    if (jsonConfig.isEmpty() || !jsonConfig.isObject()) {
        throw std::runtime_error("The configuration file, config.json, doesn't contain a valid JSON object");
    }

    // Check the JSON configuration object contains the needed keys to work
    QJsonObject configObject = jsonConfig.object();

    if (!configObject.contains("application") || !configObject.value("application").isString()) {
        throw std::runtime_error("The 'application' key is missing or is not a valid string");
    }

    if (!configObject.contains("interval") || configObject.value("interval").toInt() < 0) {
        throw std::runtime_error("The 'interval' key is missing or is not a valid integer");
    }

    // Check the optional keys are of the correct type if they exist
    if (configObject.contains("arguments") && !configObject.value("arguments").isString()) {
        throw std::runtime_error("The 'arguments' key is not a valid string");
    }

    // Check the application key represents an existing and runnable application in Windows
    QString applicationPath = configObject.value("application").toString();

    if (!Program::isValidProgram(applicationPath)) {
        throw std::runtime_error(QString("'%1' is not a valid Windows application").arg(applicationPath).toStdString());
    }

    // Inject the JSON configuration object into the Configuration Builder
    return Config(configObject);
}
