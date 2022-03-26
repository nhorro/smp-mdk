#ifndef SMP_EVENTMANAGER_H
#define SMP_EVENTMANAGER_H

#include "IEventManager.h"
#include "Service.h"

namespace Smp {
namespace Services {

class EventManager : public IEventManager, public Service
{
public:
    EventManager( ::Smp::String8 name,
                  ::Smp::String8 description,
                  ::Smp::IComposite* parent);
    ~EventManager();

     /// Get event identifier.
    /// Get unique event identifier for an event name.
    /// @param   eventName Name of the global event.
    /// @return  Event identifier for global event with given name.
    /// @remarks It is guaranteed that this method will always return
    ///          the same value when called with the same event name.
    EventId GetEventId(String8 eventName);

    /// Subscribe entry point.
    /// Subscribe an entry point to a global event.
    /// @param   event Event identifier of global event to subscribe to.
    /// @param   entryPoint Entry point to subscribe to global event.
    /// @remarks An entry point can only be subscribed once to an event.
    ///          If trying to subscribe it again, an exception of type
    ///          AlreadySubscribed is raised.
    void Subscribe(
        const EventId event, 
        const IEntryPoint* entryPoint);

    /// Unsubscribe entry point.
    /// Unsubscribe an entry point from a global event.
    /// @param   event Event identifier of global event to unsubscribe from.
    /// @param   entryPoint Entry point to unsubscribe from global event.
    /// @remarks An entry point can only be unsubscribed from an event 
    ///          after it has been subscribed before using Subscribe().
    ///          If trying to unsubscribe an entry point without subscribing
    ///          it before, a NotSubscribed exception is raised.
    void Unsubscribe(
        const EventId event, 
        const IEntryPoint* entryPoint) ;

    /// Emit a global event.
    /// @param   event Event identifier of global event to emit.
    /// @remarks This will call all entry points that are subscribed to the
    ///          global event with the given identifier.
    ///          @par
    ///          Entry points will be called synchronously in the order 
    ///          they have been subscribed to the global event.
    void Emit(const EventId event);

private:
};


}
}

#endif // SMP_EVENTMANAGER_H