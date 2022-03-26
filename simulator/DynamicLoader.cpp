
#include "DynamicLoader.h"

DynamicLoader::DynamicLoader()
{

}

DynamicLoader::~DynamicLoader()
{
    for (auto& me : this->m_models) 
    {
        me.destroy(me.model);
        dlclose(me.handle);
	}
}

void DynamicLoader::load(const std::string& filename,Smp::IComposite * parent)
{
	YAML::Node config = YAML::LoadFile(filename);
	if(config)
	{
		std::cout << "YAML opened" << std::endl;

		if ( config["models_path"] ) 
		{
            this->m_modelsPath =  config["models_path"].as<std::string>();
			std::cout << "models_path: " << this->m_modelsPath  << "\n";		
		}

		if( config["models"] )
		{
			std::cout << "Found models: " << config["models"].size()  << std::endl;
			for ( YAML::const_iterator it = config["models"].begin(); it != config["models"].end(); ++it ) 
			{
				this->loadModel(*it,parent);
			}
		}
	}
	else
	{
		// TODO: throw exception
		std::cerr << "Failed to open YAML" << std::endl;
	}
}

void DynamicLoader::loadModel(const YAML::Node& modelNode, Smp::IComposite * parent)
{
    DynamicModelEntry me;

	const std::string& className = modelNode["class"].as<std::string>();

	std::cout << "name: " << modelNode["name"].as<std::string>() << "\n";
	std::cout << "class: " << modelNode["class"].as<std::string>()  << "\n";
    std::cout << "libname: " << modelNode["libname"].as<std::string>()  << "\n";

    // Load library
    std::string fullPath = this->m_modelsPath+"/"+modelNode["libname"].as<std::string>();
    me.handle = dlopen(fullPath.c_str(), RTLD_LAZY);
    
    if (!me.handle) 
	{
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        // FIXME: throw exception
		return;
    }

    me.create = (Smp::IModel* (*)(Smp::String8 name, Smp::IComposite *parent))dlsym(me.handle, 
		(boost::format("create_%s") % className).str().c_str() );
    me.destroy = (void (*)(Smp::IModel*))dlsym(me.handle, 
		(boost::format("destroy_%s") % className).str().c_str() );
    me.model = me.create(modelNode["name"].as<std::string>().c_str(), parent);
    assert(me.model);

	// Dynamic loading of parameters. Try to improve this.
	IYAMLConfigurable* configurable = dynamic_cast<IYAMLConfigurable*>(me.model);
	assert(configurable);
	configurable->ReadInitializationParameters(modelNode["params"]);

    this->m_models.push_back(me);
	//FIXME: register with resolver
}

std::vector<DynamicLoader::DynamicModelEntry>& DynamicLoader::getModels()
{
    return this->m_models;    
}