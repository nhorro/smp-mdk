#include "CounterResetRequest.h"

CounterResetRequest::CounterResetRequest()
{

}

CounterResetRequest::~CounterResetRequest()
{

}

Smp::String8 CounterResetRequest::GetOperationName() const
{
    return "reset";
}

Smp::Int32 CounterResetRequest::GetParameterCount() const
{
    return 0;
}
    
Smp::Int32 CounterResetRequest::GetParameterIndex(Smp::String8 parameterName) const
{
    // FIXME: is Smp::IRequest::InvalidParameterName defined in SMP2 ?    
    return -1;
}

void CounterResetRequest::SetParameterValue(const Smp::Int32 index, const Smp::AnySimple value)
{
    // No parameters
    throw Smp::IRequest::InvalidParameterIndex("reset",index);
}

Smp::AnySimple CounterResetRequest::GetParameterValue(const Smp::Int32 index) const
{
    // No parameters
    throw Smp::IRequest::InvalidParameterIndex("reset",index);
}
    
void CounterResetRequest::SetReturnValue(const Smp::AnySimple value)
{
    this->returnValue = value;
}
    
Smp::AnySimple CounterResetRequest::GetReturnValue() const
{
    return this->returnValue;
}
