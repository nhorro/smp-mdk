#include "Simulator.h"

// To be implemented:
// ModelCollection
// ServiceCollection

namespace Smp
{    

Simulator::Simulator():
    Component( "root", "Simulator", nullptr)
{
    // FIXME: ver estado inicial.
    m_state = SimulatorStateKind::SSK_Building;
    //FIXME    

    // Create mandatory services

    // Create logger
    this->m_logger = new Smp::Services::Logger("logger", "Logger", this);
    this->m_logger->Log(this,"Simulator instanced");

    // FIXME: HIL Timekeeper requires HIL scheduler to be created first.

    // Create HIL Scheduler.
    this->m_scheduler = new Smp::Services::Scheduler("scheduler", "HIL Scheduler", this);
    this->m_logger->Log(this,"HIL Scheduler instanced");

    // Create HIL Timekeeper
    this->m_timeKeeper = new Smp::Services::TimeKeeper("time_keeper", "HIL Time Keeper", this);
    this->m_logger->Log(this,"HIL Timekeeper instanced");

    // Create event manager (dummy)
    this->m_eventManager = new Smp::Services::EventManager("event_manager", "Event Manager", this);
    this->m_logger->Log(this,"EventManager instanced");

    // Create publication
    this->m_publication = new Smp::Implementation::Publication();
    this->m_logger->Log(this,"Publication created");
}

Simulator::~Simulator()
{
    this->m_logger->Log(this,"Shutting down simulator");

    if (SimulatorStateKind::SSK_Executing == this->m_state)
    {
        this->Hold();
    }

    delete this->m_logger;
    delete this->m_scheduler;
    delete this->m_timeKeeper;
    delete this->m_eventManager;
    delete this->m_publication;
}   
        
    
const ModelCollection* Simulator::GetModels()
{
    return &this->m_models;
}

IModel* Simulator::GetModel(String8 name)
{    
    return this->m_modelsDict[std::string(name)];
}

void Simulator::AddModel(IModel* model)
{
    this->m_logger->Log(this,
        (boost::format("Adding model %s.") % model->GetName()).str().c_str() );
    this->m_models.push_back(model);
    // TODO: check name is not duplicated
    
    this->m_modelsDict[model->GetName()] = model;
}

const ServiceCollection* Simulator::GetServices()
{
    // FIXME: unsupported
    return nullptr;
}

IService* Simulator::GetService(String8 name)
{
    // FIXME: unsupported
    return nullptr;
}

void Simulator::AddService(IService* service)
{
    //FIXME: Unsupported
}

Services::ILogger* Simulator::GetLogger() const
{   
    return this->m_logger;
}

Services::IScheduler* Simulator::GetScheduler() const
{
    return this->m_scheduler;
}

Services::ITimeKeeper* Simulator::GetTimeKeeper() const
{
    return this->m_timeKeeper;
}

Services::IEventManager* Simulator::GetEventManager() const
{
    return this->m_eventManager;
}

SimulatorStateKind Simulator::GetState() const
{
    return this->m_state;
}

void Simulator::Publish()
{
    this->m_logger->Log(this,"Publication stage.");
    for(auto model: this->m_models)
    {
        model->Publish(this->m_publication);
    }    
}

void Simulator::Configure()
{
    this->m_logger->Log(this,"Configuration stage.");
    for(auto model: this->m_models)
    {
        model->Configure(m_logger);
    }    
}

void Simulator::Connect()
{    
    this->m_logger->Log(this,"Connection stage.");
    this->m_state = SimulatorStateKind::SSK_Connecting;

    // Call Connect for each model.
    
    for(auto model: this->m_models)
    {
        model->Connect(this);
    }

    // If everything's ok, set to initializing ok
    this->m_state = SimulatorStateKind::SSK_Initialising;
}

void Simulator::Initialise()
{
    this->m_logger->Log(this,"Initialization stage.");
    if (this->m_state != SimulatorStateKind::SSK_Initialising)
    {
        // throw invalid state
    }

    this->m_state = SimulatorStateKind::SSK_Standby;    
}

void Simulator::Hold()
{
    this->m_logger->Log(this,"Simulation at Standby state.");
    // FIXME
    this->m_state = SimulatorStateKind::SSK_Standby;
    dynamic_cast<Smp::Services::Scheduler*>(this->m_scheduler)->Stop();
}

void Simulator::Run()
{    
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }
    this->m_logger->Log(this,"Simulation is being resumed.");
    this->m_state = SimulatorStateKind::SSK_Executing;

    dynamic_cast<Smp::Services::Scheduler*>(this->m_scheduler)->Start();
}

void Simulator::Store(String8 filename)
{
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }

    this->m_logger->Log(this,"Store stage.");
    this->m_state = SimulatorStateKind::SSK_Storing;
    
    // FIXME: throw not implemented

    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Restore(String8 filename)
{
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }

    this->m_logger->Log(this,"Restore stage.");
    this->m_state = SimulatorStateKind::SSK_Restoring;

    // FIXME: throw not implemented        
    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Exit()
{
    this->m_logger->Log(this,"Exiting.");
    this->m_state = SimulatorStateKind::SSK_Exiting;
}

void Simulator::Abort()
{
    this->m_logger->Log(this,"Aborting.");
    this->m_state = SimulatorStateKind::SSK_Aborting;
}

void Simulator::AddInitEntryPoint(IEntryPoint* entryPoint)
{
    // FIXME: not implemented
}

} // end namespace Smp