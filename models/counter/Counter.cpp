#include <iostream>
#include "Counter.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"

// Initialise private fields
void Counter::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;

    // Turn Count and Reset methods into EntryPoints
    count = new CounterEntryPoint("Count", "Increment Counter", this, &Counter::Count);
    reset = new CounterEntryPoint("Reset", "Reset Counter", this, &Counter::Reset);
}

// Log a message to the logger on Reset
void Counter::Reset(void)
{
    CounterClass::Reset();
    // Send an information message to the logger
    logger->Log(this, "Reset counter", Smp::Services::LMK_Information);
}

// Publish fields to environment
void Counter::Publish(Smp::IPublication *receiver)
{
    if (state == Smp::MSK_Created)
    {
        state = Smp::MSK_Publishing;
        receiver->PublishField("counter", "Counter state", &counter);
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Created);
    }
}
// Perform custom configuration.
void Counter::Configure(Smp::Services::ILogger*) 
{
    if (state == Smp::MSK_Publishing)
    {
        state = Smp::MSK_Configured;
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Publishing);
    }
}

// Get access to services, and register entry points.
void Counter::Connect(Smp::ISimulator *simulator)
{
    if (state == Smp::MSK_Configured)
    {
        state = Smp::MSK_Connected;
        logger = simulator->GetLogger();
        scheduler = simulator->GetScheduler();
        //eventManager = simulator->GetEventManager();
        
        scheduler->AddSimulationTimeEvent(count, 0, this->frequency * 1000000000, -1);
        //eventManager->Subscribe(Smp::Services::SMP_EnterStandbyId, reset);
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}


/* Implementation-specific */

extern "C" Smp::IModel* create_Counter(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Counter(name,parent));
}

extern "C" void destroy_Counter( Smp::IModel* obj )
{
    delete dynamic_cast<Counter*>(obj);
}

void Counter::ReadInitializationParameters(const YAML::Node& paramsNode)
{    
    this->frequency =  paramsNode["frequency"].as<double>();
}