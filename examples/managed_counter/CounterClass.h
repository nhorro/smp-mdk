#include "Smp/SimpleTypes.h"

#include <iostream>

// Definition of CounterClass
class CounterClass
{
    protected:
        Smp::Int64 counter; // Protected field to store counter

    public:
        
        // Public methods to count, to reset and to return the counter
        virtual void Count(void);
        virtual void Reset(void);
        virtual Smp::Int64 get_Counter(void);

        // Public constructor.
        CounterClass() : counter(0) {}
};