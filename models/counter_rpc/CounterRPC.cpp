#include <iostream>
#include "CounterRPC.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"

// Initialise private fields
void CounterRPC::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;

    counter = 0;

    // Turn Count and Reset methods into EntryPoints
    count = new CounterEntryPoint("Count", "Increment Counter", this, &CounterRPC::Count);
    reset = new CounterEntryPoint("Reset", "Reset Counter", this, &CounterRPC::Reset);
}

// Log a message to the logger on Reset
void CounterRPC::Reset(void)
{
    this->counter = 0;

    // Send an information message to the logger
    logger->Log(this, "Reset counter", Smp::Services::LMK_Information);
}

// Publish fields to environment
void CounterRPC::Publish(Smp::IPublication *receiver)
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
void CounterRPC::Configure(Smp::Services::ILogger*) 
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
void CounterRPC::Connect(Smp::ISimulator *simulator)
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

void CounterRPC::Count(void)
{
    this->counter++;
    std::cout << "Count is " << this->counter << std::endl;
}


Smp::Int64 CounterRPC::get_Counter(void)
{
    return this->counter;
}



// IDynamicInvocation
Smp::IRequest* CounterRPC::CreateRequest(Smp::String8 operationName)
{
    if(!strcmp("operation",operationName))
    {
        throw Smp::IDynamicInvocation::InvalidOperationName(operationName);
    }
    return new CounterResetRequest();
}

void CounterRPC::Invoke(Smp::IRequest* request)
{    
    CounterResetRequest* req = dynamic_cast<CounterResetRequest*>(request);
    assert(req);
    this->Reset();
    //req->SetReturnValue(this->count);
}

void CounterRPC::DeleteRequest(Smp::IRequest* request)
{
    delete request;
}

/* Platform-specific */

extern "C" Smp::IModel* create_CounterRPC(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new CounterRPC(name,parent));
}

extern "C" void destroy_CounterRPC( Smp::IModel* obj )
{
    delete dynamic_cast<CounterRPC*>(obj);
}

void CounterRPC::ReadInitializationParameters(const YAML::Node& paramsNode)
{    
    this->frequency =  paramsNode["frequency"].as<double>();
}