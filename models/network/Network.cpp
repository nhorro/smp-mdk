#include "Network.h"

// Initialise private fields
void Bus::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;
}

// Publish fields to environment
void Bus::Publish(Smp::IPublication *receiver)
{
    if (state == Smp::MSK_Created)
    {
        state = Smp::MSK_Publishing;
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Created);
    }
}
// Perform custom configuration.
void Bus::Configure(Smp::Services::ILogger*) 
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
void Bus::Connect(Smp::ISimulator *simulator)
{
    if (state == Smp::MSK_Configured)
    {
        state = Smp::MSK_Connected;
        logger = simulator->GetLogger();
        scheduler = simulator->GetScheduler();

        for (auto& nodeName: this->m_nodeNames) 
        {
            std::cout << "Bus. Connecting node: " << nodeName << "\n";

            Node* node = dynamic_cast<Node*>(simulator->GetModel(nodeName.c_str()));
            assert(node);
            this->Attach(node);
        }    
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}

void Bus::Attach(Node* node)
{
    node->SetBus(this);
    this->m_nodes.push_back(node);
}

void Bus::Inject(Message* msg)
{
    for(auto& node: this->m_nodes)
    {
        if ( node->GetId() != msg->originator_id )
        {
            node->Receive(msg);
        }
    }    

    delete msg;
}

/* Implementation-specific */

extern "C" Smp::IModel* create_Bus(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Bus(name,parent));
}

extern "C" void destroy_Bus( Smp::IModel* obj )
{
    delete dynamic_cast<Bus*>(obj);
}

void Bus::ReadInitializationParameters(const YAML::Node& paramsNode)
{   
    std::cout << "Initializing bus. Nodes: " << paramsNode["nodes"].size() << std::endl;    
    for (YAML::const_iterator it  = paramsNode["nodes"].begin(); 
                              it != paramsNode["nodes"].end(); ++it) 
    {    
        std::cout << "Adding node: " << it->as<std::string>() << "\n";
        this->m_nodeNames.push_back(it->as<std::string>());
    }
}


/* Node */

// Initialise private fields
void Node::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;

    sync = new NodeEntryPoint("Sync", "Send SYNC messages", this, &Node::Sync);
}

// Publish fields to environment
void Node::Publish(Smp::IPublication *receiver)
{
    if (state == Smp::MSK_Created)
    {
        state = Smp::MSK_Publishing;
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Created);
    }
}
// Perform custom configuration.
void Node::Configure(Smp::Services::ILogger*) 
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
void Node::Connect(Smp::ISimulator *simulator)
{
    if (state == Smp::MSK_Configured)
    {
        state = Smp::MSK_Connected;
        logger = simulator->GetLogger();
        scheduler = simulator->GetScheduler();
        //eventManager = simulator->GetEventManager();
        
        if (this->m_isMaster)
        {
            this->scheduler->AddSimulationTimeEvent(sync, 0, 1000000000, -1);
        }
        
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}

void Node::Transmit(Message* msg)
{    
    msg->originator_id = this->m_id;

    assert(this->m_bus);
    this->m_bus->Inject(msg);
}

void Node::Receive(Message* msg)
{
    std::cout << this->GetName() << ": Message received" << std::endl;
}

void Node::Sync()
{    
    std::cout << this->GetName() << " sending SYNC" << std::endl;
    
    Message* msg = new Message();
        
    msg->id = 0x0BADBABE;
    msg->len = 8;
    msg->data[0] = 0x10;
    msg->data[1] = 0x12;
    msg->data[2] = 0x13;
    msg->data[3] = 0x14;
    msg->data[4] = 0x15;
    msg->data[5] = 0x16;
    msg->data[6] = 0x17;
    msg->data[7] = 0x18;

    this->Transmit(msg);
}

/* Implementation-specific */

extern "C" Smp::IModel* create_Node(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Node(name,parent));
}

extern "C" void destroy_Node( Smp::IModel* obj )
{
    delete dynamic_cast<Node*>(obj);
}

void Node::ReadInitializationParameters(const YAML::Node& paramsNode)
{    
    this->m_id = paramsNode["id"].as<uint32_t>();
    this->m_isMaster = paramsNode["master"].as<bool>();
}