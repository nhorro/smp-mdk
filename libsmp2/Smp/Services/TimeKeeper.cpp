#include "TimeKeeper.h"

namespace Smp {
namespace Services {

TimeKeeper::TimeKeeper( ::Smp::String8 name,
                        ::Smp::String8 description,
                        ::Smp::IComposite* parent)
    :
        Service(name,description,parent)
{
    m_scheduler = dynamic_cast<Scheduler*>(dynamic_cast<ISimulator*>(parent)->GetScheduler());
    assert(m_scheduler);
}

TimeKeeper::~TimeKeeper()
{

}

Duration TimeKeeper::GetSimulationTime()
{
    // HIL TimeKeeper gets time from scheduler    
    return m_scheduler->GetSimulationTime();
}

DateTime TimeKeeper::GetEpochTime()
{
    return m_epochTime;
}

Duration TimeKeeper::GetMissionTime()
{
    return m_missionTime;
}

DateTime TimeKeeper::GetZuluTime()
{
    return m_zuluTime;
}

void TimeKeeper::SetEpochTime(const DateTime epochTime)
{
    m_epochTime = epochTime;
}

void TimeKeeper::SetMissionStart(const DateTime missionStart)
{
    m_missionStart = missionStart;
}

void TimeKeeper::SetMissionTime(const Duration missionTime)
{
    m_missionTime = missionTime;
}


} // end namespace Services
} // end namespace Smp