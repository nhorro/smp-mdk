#ifndef BUS_H
#define BUS_H

#include <iostream>

#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/IEventManager.h"

#include "IYAMLConfigurable.h"

#include "Message.h"

class Node;

/// Bus model
class Bus : 
    public virtual Smp::IModel,
    public IYAMLConfigurable
{
private:
    char* name;                     ///< Name of model.
    Smp::ModelStateKind state;      ///< Model state.
    Smp::IComposite *parent;        ///< Parent component.
    Smp::Services::ILogger *logger;         ///< Logger service.
    Smp::Services::IScheduler *scheduler;   ///< Scheduler service.
    //Smp::Services::IEventManager *eventManager; ///< EventManager service.
    void Init(); ///< Init private fields.

public:
    Bus(Smp::String8 name, Smp::IComposite *parent) 
    {
        Init();
        this->name = strdup(name);
        this->state = Smp::MSK_Created;
        this->parent = parent;
    }
    
    virtual ~Bus()
    {
        if (name) free(name);
    }
        
    // IModel methods
    virtual Smp::String8 GetName() const { return name; }
    virtual Smp::String8 GetDescription() const { return "Bus Model"; }
    virtual Smp::IComposite* GetParent() const { return parent; }
    virtual Smp::ModelStateKind GetState() const { return state; }
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

    // Non-SMP2
    void ReadInitializationParameters(const YAML::Node& paramsNode);


    void Attach(Node* node);   
    void Inject(Message* msg); 
    
private:    
    std::vector<Node*> m_nodes;
    std::vector<std::string> m_nodeNames;
};


/// Node model.
class Node : 
    public virtual Smp::IModel,
    public IYAMLConfigurable
{
private:
        /// Private helper class for entry points
        class NodeEntryPoint : public Smp::IEntryPoint
        {
            private:
                char* name; ///< Name of entry point.
                char* description; ///< Description.
                Node* publisher; ///< Entry point publisher.
                void (Node::*entryPoint)(void); ///< Instance method.
            
            public:
                /// Constructor with name, description, publisher and entry point.
                NodeEntryPoint(
                    Smp::String8 name,
                    Smp::String8 description,
                    Node* publisher,
                    void (Node::*entryPoint)(void) )
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
    char* name;                                 ///< Name of model.
    Smp::ModelStateKind state;                  ///< Model state.
    Smp::IComposite *parent;                    ///< Parent component.
    Smp::Services::ILogger *logger;             ///< Logger service.
    Smp::Services::IScheduler *scheduler;       ///< Scheduler service.    
    void Init();                                ///< Init private fields.    

    NodeEntryPoint *sync; ///< Entry point for sending sync messages (master only).
public:
    Node(Smp::String8 name, Smp::IComposite *parent)
    {
        Init();
        this->name = strdup(name);
        this->state = Smp::MSK_Created;
        this->parent = parent;
    }
    
    virtual ~Node()
    {
        if (name) free(name);
    }
    
    // IModel methods
    virtual Smp::String8 GetName() const { return name; }
    virtual Smp::String8 GetDescription() const { return "Node Model"; }
    virtual Smp::IComposite* GetParent() const { return parent; }
    virtual Smp::ModelStateKind GetState() const { return state; }
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

    // Implementation-specific
    void ReadInitializationParameters(const YAML::Node& paramsNode);

    Bus* GetBus() { return this->m_bus; }
    void SetBus(Bus* bus) { this->m_bus = bus; }
    void Transmit(Message* msg);
    void Receive(Message* msg);
    uint32_t GetId() const { return this->m_id; }
    void Sync();
private:
    Bus* m_bus;
    uint32_t m_id;
    bool m_isMaster;
};

#endif // BUS_H