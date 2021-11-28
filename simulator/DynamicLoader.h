#ifndef DYNAMIC_LOADER_H
#define DYNAMIC_LOADER_H

#include <iostream>
#include <vector>
#include <boost/format.hpp>

#include <dlfcn.h>
#include <yaml-cpp/yaml.h>

#include "Mdk/Model.h"
#include "Smp/IComposite.h"
#include "IYAMLConfigurable.h"

class DynamicLoader {
public:
    struct DynamicModelEntry{
        void* handle;
        Smp::IModel* (*create)(Smp::String8 name, Smp::IComposite *parent);
        void (*destroy)(Smp::IModel*);
        Smp::IModel* model;
    };

	DynamicLoader();
	~DynamicLoader();

	void load(const std::string& filename, Smp::IComposite * parent);
    std::vector<DynamicLoader::DynamicModelEntry>& getModels();
private:
    std::string m_modelsPath;
    std::vector<DynamicModelEntry> m_models;
    void loadModel(const YAML::Node& modelNode,Smp::IComposite * parent);    
};

#endif // DYNAMIC_LOADER_H