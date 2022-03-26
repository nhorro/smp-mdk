#include "Service.h"

namespace Smp {
namespace Services {

Service::Service()
{

}

Service::Service(::Smp::String8 name,
                 ::Smp::String8 description,
                 ::Smp::IComposite* parent)
        :
            Component(name,description,parent)
{
    
}

Service::~Service()
{
    
}

} // Smp
} // Services