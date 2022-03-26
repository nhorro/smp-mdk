#include "Resolver.h"

namespace Smp {
namespace Services {

Resolver::Resolver()
{

}

Resolver::~Resolver()
{

}

IComponent* Resolver::ResolveAbsolute(String8 absolutePath)
{
    return nullptr;
}

IComponent* Resolver::ResolveRelative(String8 relativePath, IComponent* sender)
{
    // FIXME: Not implemented
    return nullptr;
}

} // end namespace Services
} // end namespace Smp