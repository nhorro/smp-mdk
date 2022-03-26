#include "Scheduler.h"

namespace Smp {
namespace Services {

HWTimedEvent::HWTimedEvent(  boost::asio::io_service& ioservice,
                             Duration offsetInterval, 
                             int count,
                             Duration interval,
                             const IEntryPoint* entryPoint,
                             EventId eventId,
                             Scheduler& owner)
    :           
      m_timer(ioservice)
    , m_entryPoint(entryPoint)
    , m_offsetInterval(offsetInterval)
    , m_count(count)
    , m_interval(interval)
    , m_eventId(eventId)
    , m_owner(owner)
{
    // Schedule start to be ran by the io_service
    ioservice.post(boost::bind(&HWTimedEvent::start, this));    
}

HWTimedEvent::~HWTimedEvent() 
{
    std::cout << "Event destroyed" << std::endl;
}


void HWTimedEvent::execute(boost::system::error_code const& ec)
{
    if (!ec)
    {
        if (m_count)
        {
            m_timer.expires_at( m_timer.expires_at() + 
                                boost::posix_time::microseconds(m_interval/1000) );
            this->startWait();

            // m_count == -1 is infinite
            if( m_count != -1 )
            {
                m_count--;
            }
        }
        else
        {
            m_owner.RemoveEvent(m_eventId);
        }
        m_entryPoint->Execute();
    }
    else
    {
        if ( boost::asio::error::operation_aborted == ec) 
        {
            // FIXME
            //m_logger->Log(nullptr,"Event was cancelled.", Smp::Services::LMK_Error);
        }
        else 
        {
            // FIXME
            //m_logger->Log(nullptr,"Unknown error handling event.", Smp::Services::LMK_Error);
        }

        m_owner.RemoveEvent(m_eventId);
    }
}

void HWTimedEvent::start()
{
    m_timer.expires_from_now(boost::posix_time::microseconds(m_offsetInterval/1000));
    this->startWait();
}

void HWTimedEvent::cancel()
{
    m_timer.cancel();
}


void HWTimedEvent::startWait()
{
    m_timer.async_wait(boost::bind(&HWTimedEvent::execute
        , this
        , boost::asio::placeholders::error));
}

Scheduler::Scheduler(::Smp::String8 name,
                     ::Smp::String8 description,
                     ::Smp::IComposite* parent)
    :
          Service(name,description,parent)
        , m_isRunning(false)
        , eventIdCounter(0)
{
    m_logger = dynamic_cast<ISimulator*>(parent)->GetLogger();
    m_logger->Log(this,"Scheduler instanced.", Smp::Services::LMK_Information);
}

Scheduler::~Scheduler()
{    
    this->Stop();   
}

void Scheduler::AddImmediateEvent(const IEntryPoint* entryPoint)
{
    if(m_isRunning)
    {
        m_logger->Log(this,"Adding inmediate events to scheduler.", Smp::Services::LMK_Debug);
        const std::lock_guard<std::mutex> lock(m_eventsMutex);
        EventId eventId = ++eventIdCounter;
        m_events[eventId] = std::make_shared<HWTimedEvent>( *m_ioservice, 
                                                            0, 
                                                            1,
                                                            0, 
                                                            entryPoint,
                                                            eventId, *this );
    }
    else
    {
        m_logger->Log(this,"Inmediate events are only supported when running.", Smp::Services::LMK_Error);
    }
}

EventId Scheduler::AddSimulationTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration simulationTime,
    const Duration cycleTime,
    const Int64 count)
{
    // If scheduler is running, post event to hw clock scheduler,
    // otherwise, store it in a temporary structure to schedule when scheduler starts.
    if(m_isRunning)
    {
        const std::lock_guard<std::mutex> lock(m_eventsMutex);
        Duration offsetInterval = simulationTime;

        if(offsetInterval > 0 )
        {
            EventId eventId = ++eventIdCounter;
            m_events[eventId] = std::make_shared<HWTimedEvent>( *m_ioservice, 
                                                                offsetInterval, 
                                                                count,
                                                                cycleTime,  
                                                                entryPoint,
                                                                eventId, *this );
        }
        else
        {
            m_logger->Log(this,"Cannot post event in the past.", Smp::Services::LMK_Error);
        }        

    }   
    else
    {
        EventId eventId = ++eventIdCounter;
        m_pendingEvents[eventId] = PendingEvent{ entryPoint, simulationTime, cycleTime, count };
    }
    
    return 0; 
}

EventId Scheduler::AddMissionTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration missionTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
    return 0; 
}

EventId Scheduler::AddEpochTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime epochTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
    return 0; 
}

EventId Scheduler::AddZuluTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime zuluTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
    return 0; 
}

void Scheduler::SetEventSimulationTime(
    const EventId event, 
    const Duration simulationTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}    

void Scheduler::SetEventMissionTime(
    const EventId event, 
    const Duration missionTime)
{
    //m_logger->Log(this,"Scheduler instanced.", Smp::Services::LMK_Information);
    // This is not so straightforward in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}

void Scheduler::SetEventEpochTime(
    const EventId event, 
    const DateTime epochTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}

void Scheduler::SetEventZuluTime(
    const EventId event, 
    const DateTime zuluTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}

void Scheduler::SetEventCycleTime( const EventId event, const Duration cycleTime)
{
    // This is not so useful in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}

void Scheduler::SetEventCount(const EventId event, const Int64 count)
{
    // This is not so useful in HIL.
    // Unsupported
    // FIXME: Change exception type when available. 
    throw InvalidObjectType(this);
}

void Scheduler::RemoveEvent(const EventId event)
{
    const std::lock_guard<std::mutex> lock(m_eventsMutex);
    m_events[event]->cancel();
}


void Scheduler::Start()
{
    if(m_isRunning)
    {
        // Already started
        return;
    }

    m_ioservice = std::make_unique<boost::asio::io_service>();
    m_work = std::make_unique<boost::asio::io_service::work>(*m_ioservice);
    m_isRunning = true;

    m_simulationStart = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // All events registered by the scheduler should be actually scheduled in the HW clock.    
    for (auto const& x : m_pendingEvents)
    {        
        m_events[x.first] = std::make_shared<HWTimedEvent>( *m_ioservice,                                                             
                                                            x.second.simulationTime,   // offsetInterval (ns)
                                                            x.second.count,            // count (-1=infinite)
                                                            x.second.cycleTime,        // cycleTime (ns)
                                                            x.second.entryPoint,       // EntryPoint
                                                            x.first,  *this ); 
    }
    m_pendingEvents.clear();
    m_workingThread = std::make_unique<std::thread>([this]() { m_ioservice->run(); } );    
}

void Scheduler::Stop()
{
    if(!m_isRunning)
    {
        return;
    }

    // WARNING All scheduled events will be lost!
    if (m_events.size() > 0 )
    {
        m_events.clear();
    }

    m_ioservice->stop();
    m_workingThread->join();
    m_isRunning = false;
}

    

Duration Scheduler::GetSimulationTime() const
{
    if (m_isRunning)
    {
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds> (t - m_simulationStart).count();
    }
    else
    {
        return 0;
    }    
}

} // end namespace Services
} // end namespace Smp