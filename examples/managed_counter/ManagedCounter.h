#include "CounterClass.h"
#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/IEventManager.h"
#include "Smp/Management/IManagedModel.h"
#include "Smp/Management/IEntryPointPublisher.h"

/// This class turns the CounterClass into an Smp model.
class ManagedCounter : 
    public CounterClass, 
    public virtual Smp::Management::IManagedModel,
    public virtual Smp::Management::IEntryPointPublisher
{
    private:
        
        /// Private helper class for entry points
        class CounterEntryPoint : public Smp::IEntryPoint
        {
            private:
                char* name; ///< Name of entry point.
                char* description; ///< Description.
                ManagedCounter* publisher; ///< Entry point publisher.
                void (ManagedCounter::*entryPoint)(void); ///< Instance method.
            
            public:
                /// Constructor with name, description, publisher and entry point.
                CounterEntryPoint(
                    Smp::String8 name,
                    Smp::String8 description,
                    ManagedCounter* publisher,
                    void (ManagedCounter::*entryPoint)(void) )
                {
                    this->name = strdup(name);
                    this->description = strdup(description);
                    this->publisher = publisher;
                    this->entryPoint = entryPoint;
                }

                virtual Smp::String8 GetName() const { return name; }
                
                virtual Smp::String8 GetDescription() const { return description; }
                
                virtual Smp::IComponent* GetOwner() const { return publisher; }
                
                void Execute() const { (publisher->*entryPoint)(); }
        };

private:
    char* name; ///< Name of model.
    char* description;  ///< Description of model.
    Smp::ModelStateKind state; ///< Model state.
    Smp::IComposite *parent; ///< Parent component.
    Smp::Services::ILogger *logger; ///< Logger service.
    Smp::Services::IScheduler *scheduler; ///< Scheduler service.
    //Smp::Services::IEventManager *eventManager; ///< EventManager service.
    CounterEntryPoint *count; ///< Entry point for Count.
    CounterEntryPoint *reset; ///< Entry point for Reset.
    Smp::EntryPointCollection *entryPoints; ///< Collection of entry points.
    void Init(); ///< Init private fields.

public:
    ManagedCounter(Smp::String8 name, Smp::IComposite *parent) : CounterClass()
    {
        Init();
        this->name = strdup(name);
        this->state = Smp::MSK_Created;
        this->parent = parent;
    }
    
    virtual ~ManagedCounter()
    {
        if (name) free(name);
        if (description) free(description);
    }
    
    virtual void Reset(void); ///< Reset method logs a message
    
    // IObject, IComponent and IModel methods
    virtual Smp::String8 GetName() const { return name; }
    virtual Smp::String8 GetDescription() const { return description; }
    virtual Smp::IComposite* GetParent() const { return parent; }
    virtual Smp::ModelStateKind GetState() const { return state; }
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

    // IManagedObject, IManagedComponent and IManagedModel methods
    virtual void SetName(Smp::String8 name);
    virtual void SetDescription(Smp::String8 description);
    virtual void SetParent(Smp::IComposite *parent);
    virtual Smp::AnySimple GetFieldValue(Smp::String8 fullName);
    virtual void SetFieldValue(Smp::String8 fullName, const Smp::AnySimple value);
    virtual void GetArrayValue(Smp::String8 fullName, const Smp::AnySimpleArray
        values, const Smp::Int32 length) {}
    virtual void SetArrayValue(Smp::String8 fullName, const Smp::AnySimpleArray
        values, const Smp::Int32 length) {}
    // IEntryPointPublisher methods
    virtual const Smp::EntryPointCollection *GetEntryPoints() const;
    virtual Smp::IEntryPoint *GetEntryPoint(Smp::String8 entryPointName) const;
};