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
        
        scheduler->AddSimulationTimeEvent(count, 0, 1000000000, -1);
        //eventManager->Subscribe(Smp::Services::SMP_EnterStandbyId, reset);
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}