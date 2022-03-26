#ifndef YAML_CONFIGURABLE_H
#define YAML_CONFIGURABLE_H

#include <yaml-cpp/yaml.h>

class IYAMLConfigurable
{
public:
    virtual void ReadInitializationParameters(const YAML::Node& paramsNode) = 0;
};

#endif // YAML_CONFIGURABLE_H