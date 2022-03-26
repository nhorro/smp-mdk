#ifndef CONTERRESETREQUEST_H
#define CONTERRESETREQUEST_H

#include "Smp/IRequest.h"

class CounterResetRequest : public Smp::IRequest
{
public:
    CounterResetRequest();
    virtual ~CounterResetRequest();

    virtual Smp::String8 GetOperationName() const;
    virtual Smp::Int32 GetParameterCount() const;
    virtual Smp::Int32 GetParameterIndex(Smp::String8 parameterName) const;
    virtual void SetParameterValue(const Smp::Int32 index, const Smp::AnySimple value);
    virtual Smp::AnySimple GetParameterValue(const Smp::Int32 index) const;
    virtual void SetReturnValue(const Smp::AnySimple value);
    virtual Smp::AnySimple GetReturnValue() const;
private:
    Smp::AnySimple returnValue;
};

#endif // CONTERRESETREQUEST_H