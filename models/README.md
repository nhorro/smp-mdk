Example models
==============

This module contains models that can be instanced in the simulator.

- Counter example from SMP 2.0 Handbook - 1.2 Section 3 with required the modifications to use in the simulator (see below).
- A simple network model made from a bus and two or more nodes.

Implementation-specific considerations
--------------------------------------

While it is a design driver for the [SMP2 framework implementation](../libsmp2) and [SMP2 simulation infrastructure](../simulator) to rely on as few implementation-specific details as possible to simplify portability, some considerations need to be taken for dynamic libraries that contain C++ SMP2 models.

- Models are dynamically loaded from `.so` files specified in a YAML configuration file at runtime.
- Each `.so` must provide a C interface for creation an destruction of model classes as depicted in the example below.
- Models can be configured using parameters in the YAML. This configuration mechanism is different from the proposed SMP2 assemblies.

**Symbol exportation in `.so`**

For each SMP2 model that implements `Smp::IModel` and is to be instanced by the user the methods `create_CLASSNAME` and `destroy_CLASSNAME` have to be provided. For example, if the class is `Counter`:

~~~c++
extern "C" Smp::IModel* create_Counter(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Counter(name,parent));
}

extern "C" void destroy_Counter( Smp::IModel* obj )
{
    delete dynamic_cast<Counter*>(obj);
}
~~~

**Configuration at runtime**

Currently, the simulator does not provide support for SMP2 assemblies. 
However, models can implement the [IYAMLConfigurable](../libsmp2/IYAMLConfigurable.h) interface (not from the SMP2 standard) to read parameters from the configuration YAML at execution time.

If implemented, `ReadInitializationParameters` is called at model instantation giving read acces to the YAML node `params`.

~~~c++
#include <yaml-cpp/yaml.h>

class IYAMLConfigurable
{
public:
    virtual void ReadInitializationParameters(const YAML::Node& paramsNode) = 0;
};
~~~

**Example configuration entry from YAML file**

The following example instances two [counter models](./counter) from the SMP2 Handbook. For each instance a unique name is provided, its class, and the path of the `.so`.
Instantiation parameters are indicated in the `params` entry.

~~~yaml
# ...
models:
  - name: counter1
    class: Counter
    libname: counter/libcounter.so
    params: 
      frequency: 0.5
  - name: counter2
    class: Counter
    libname: counter/libcounter.so
    params: 
      frequency: 1.0
~~~