#ifndef SMP_SERVICE_H
#define SMP_SERVICE_H

#include "Smp/IService.h"
#include "Mdk/Component.h"

namespace Smp {
namespace Services {

class Service: public IService, public Mdk::Component {
public:    
    Service();
    Service(
        ::Smp::String8 name,
        ::Smp::String8 description,
        ::Smp::IComposite* parent);    
    ~Service();
private:
};


} // end namespace Services
} // end namespace Smp

#endif // SMP_SERVICE_H