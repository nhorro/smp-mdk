#ifndef SMP_RESOLVER_H
#define SMP_RESOLVER_H

#include "IResolver.h"

namespace Smp {
namespace Services {

// Minimal implementation. Holds a table with path and model.
class Resolver : public IResolver, public Service
{
public:
    Resolver();

    ~Resolver();    

    /// Resolve reference to component via absolute path.
    /// @param   absolutePath Absolute path to component in simulation.
    /// @return  Component identified by path, or null for invalid path.
    IComponent* ResolveAbsolute(String8 absolutePath);

    /// Resolve reference to component via relative path.
    /// @param   relativePath Relative path to component in simulation.
    /// @param   sender Component that asks for resolving the reference.
    /// @return  Component identified by path, or null for invalid path.
    IComponent* ResolveRelative(String8 relativePath, IComponent* sender);    

private:
    Smp::IComponent* m_root;
};

} // end namespace Services
} // end namespace Smp

#endif // SMP_RESOLVER_H