#ifndef SMP_TIMEKEEPER_H
#define SMP_TIMEKEEPER_H

#include "Smp/ISimulator.h"
#include "Smp/Exceptions.h"
#include "Smp/Services/ITimeKeeper.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/Scheduler.h"
#include "Smp/Services/Service.h"

namespace Smp {
namespace Services {

class TimeKeeper : public ITimeKeeper, public Service
{
public:
    TimeKeeper(::Smp::String8 name,
               ::Smp::String8 description,
               ::Smp::IComposite* parent);

    ~TimeKeeper();

    /// Return simulation time.
    /// Simulation time is a relative time that starts at 0.
    /// @return  Current simulation time.
    Duration GetSimulationTime();

    /// Return Epoch time.
    /// Epoch time is an absolute time with a fixed offset to simulation 
    /// time.
    /// @return  Current epoch time.
    /// @remarks Epoch time typically progresses with simulation
    ///          time, but can be changed with SetEpochTime().
    DateTime GetEpochTime();

    /// Return Mission time.
    /// Mission time is a relative time with a fixed offset to epoch
    /// time.
    /// @return  Current mission time.
    /// @remarks Mission time typically progresses with epoch
    ///          time, but can be changed with SetMissionTime().
    Duration GetMissionTime();

    /// Return Zulu time.
    /// Zulu time is a system dependent time and not related to simulation
    /// time.
    /// @return  Current Zulu time.
    /// @remarks Zulu time is typically related to the system clock of the
    ///          computer.
    DateTime GetZuluTime();

    /// Set Epoch time.
    /// Changes the offset between simulation time and epoch time.
    /// @param     epochTime New epoch time.
    /// @remarks This shall raise an SMP_EpochTimeChanged event.
    ///          As mission time is relative to epoch time, this will 
    ///          change the mission time as well.
    void SetEpochTime(const DateTime epochTime);

    /// Set Mission start.
    /// Changes the offset between mission time and epoch time.
    /// The mission time itself will be calculated as the offset
    /// between the current epoch time and the given mission start.
    /// @param      missionStart New mission start date and time.
    /// @remarks This shall raise an SMP_MissionTimeChanged event.
    void SetMissionStart(const DateTime missionStart);

    /// Set Mission time.
    /// Changes the offset between mission time and epoch time.
    /// @param      missionTime New mission time.
    /// @remarks This shall raise an SMP_MissionTimeChanged event.
    void SetMissionTime(const Duration missionTime);
private:    
    Scheduler* m_scheduler;
    Duration m_simulationTime;
    Duration m_missionTime;
    DateTime m_missionStart;
    DateTime m_epochTime;
    DateTime m_zuluTime;
};

} // end namespace Services
} // end namespace Smp

#endif // SMP_TIMEKEEPER_H