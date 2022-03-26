#include "EventManager.h"

namespace Smp {
namespace Services {

EventManager::EventManager( ::Smp::String8 name,
                            ::Smp::String8 description,
                            ::Smp::IComposite* parent )
    :
        Service(name,description,parent)
{

}

EventManager::~EventManager()
{

}

EventId EventManager::GetEventId(String8 eventName)
{
    // FIXME
    return 999;    
}

void EventManager::Subscribe(
        const EventId event, 
        const IEntryPoint* entryPoint)
{
    // FIXME: To be implemented   
}

    
void EventManager::Unsubscribe(
        const EventId event, 
        const IEntryPoint* entryPoint)
{
    // FIXME: To be implemented   
}

void EventManager::Emit(const EventId event)
{
    // FIXME: To be implemented   
}

} // end namespace Services
} // end namespace Smp