#include <iostream>
#include "ManagedCounter.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"

// Initialise private fields
void ManagedCounter::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;

    // Turn Count and Reset methods into EntryPoints
    count = new CounterEntryPoint("Count", "Increment Counter", this, &CounterClass::Count);
    reset = new CounterEntryPoint("Reset", "Reset Counter", this, &ManagedCounter::Reset);

    description = NULL;
    entryPoints = new Smp::EntryPointCollection();
    entryPoints->push_back(count);
    entryPoints->push_back(reset);
}

void ManagedCounter::SetName(Smp::String8 name)
{
    if (this->name) free(this->name);
        this->name = strdup(name);
}

void ManagedCounter::SetDescription(Smp::String8 description)
{
    if (this->description) free(this->description);
        this->description = strdup(description);
}

void ManagedCounter::SetParent(Smp::IComposite *parent)
{
    this->parent = parent;
}

Smp::AnySimple ManagedCounter::GetFieldValue(Smp::String8 fieldName)
{
    Smp::AnySimple returnValue;
    if (strcmp(fieldName, "counter") == 0)
    {
        returnValue.type = Smp::ST_Int64;
        returnValue.value.int64Value = counter;
        return returnValue;
    }
    else
        throw InvalidFieldName(fieldName);
}

void ManagedCounter::SetFieldValue(Smp::String8 fieldName, const Smp::AnySimple value)
{
    if (strcmp(fieldName, "counter") == 0)
    {
        if (value.type == Smp::ST_Int64)
            counter = value.value.int64Value;
        else
            throw Smp::InvalidAnyType(value.type, Smp::ST_Int64);
    }
    else
        throw InvalidFieldName(fieldName);
}

const Smp::EntryPointCollection *ManagedCounter::GetEntryPoints() const
{
    return entryPoints;
}

Smp::IEntryPoint* ManagedCounter::GetEntryPoint(Smp::String8 entryPointName) const
{
    if (strcmp(entryPointName, "Count") == 0)
        return count;
    else if (strcmp(entryPointName, "Reset") == 0)
        return reset;
    else
        return NULL;
}

// Log a message to the logger on Reset
void ManagedCounter::Reset(void)
{
    CounterClass::Reset();
    // Send an information message to the logger
    logger->Log(this, "Reset counter", Smp::Services::LMK_Information);
}

// Publish fields to environment
void ManagedCounter::Publish(Smp::IPublication *receiver)
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
void ManagedCounter::Configure(Smp::Services::ILogger*) 
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
void ManagedCounter::Connect(Smp::ISimulator *simulator)
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