#include "SimulatorService.h"

SimulatorService::SimulatorService(int rpc_port, int rpc_timeout_ms, const std::string& config)
	:
        rpc_transport(
            dynamic_cast<rpc_transport_base*>( 
                new zmq_reqrep_transport(rpc_port, rpc_timeout_ms) 
            )
        )
    , 	server(rpc_transport)
    ,   m_configFilename(config)
{
	this->registerRPCMethods();
}

SimulatorService::~SimulatorService()
{
	this->server.stop();
}

void SimulatorService::registerRPCMethods() 
{
	this->server.register_handler( "hello", 
		std::bind( &SimulatorService::rpc_hello,  this, std::placeholders::_1) 
	);

	this->server.register_handler( "model_request", 
		std::bind( &SimulatorService::rpc_model_request,  this, std::placeholders::_1) 
	);
}

void SimulatorService::setupAndStart()
{
	// Access services from simulator	
	this->m_sim.GetLogger()->Log(nullptr,"Simulation service started", Smp::Services::LMK_Information);

	// 1. Create models
	this->m_sim.GetLogger()->Log(nullptr,"Creating models", Smp::Services::LMK_Information);

	// TODO load config and add models

	this->m_dl.load(this->m_configFilename,dynamic_cast< Smp::IComposite*>(&this->m_sim));
	for (auto& me : this->m_dl.getModels()) {
    	this->m_sim.AddModel(me.model);
	}

	// Publish variables in the simulation environment
	this->m_sim.GetLogger()->Log(nullptr,"Publishing model variables", Smp::Services::LMK_Information);
	this->m_sim.Publish();

	// Configure
	this->m_sim.GetLogger()->Log(nullptr,"Configuring models", Smp::Services::LMK_Information);
	this->m_sim.Configure();

	// Connect
	this->m_sim.GetLogger()->Log(nullptr,"Connecting models", Smp::Services::LMK_Information);
	this->m_sim.Connect();

	// Initialize
	this->m_sim.GetLogger()->Log(nullptr,"Initializing models", Smp::Services::LMK_Information);
	this->m_sim.Initialise();

	server.start();

	// Run simulation
	this->m_sim.GetLogger()->Log(nullptr,"Running simulation", Smp::Services::LMK_Information);
	this->m_sim.Run();
}

void SimulatorService::cleanupAndShutdown()
{		
	this->m_sim.GetLogger()->Log(nullptr,"Holding simulation", Smp::Services::LMK_Information);
	this->m_sim.Hold();

	// Exit simulation
	this->m_sim.GetLogger()->Log(nullptr,"Leaving simulation", Smp::Services::LMK_Information);
	this->m_sim.Exit();
}




jsonrpcpp::Response SimulatorService::rpc_model_request(jsonrpcpp::request_ptr request)
{
	// Obtain IModel. FIXME: Use resolver.
	Smp::IModel* model = this->m_sim.GetModel(request->params().get<std::string>("model").c_str());
	assert(model);

	// Obtain IDynamicInvocation 
	Smp::IDynamicInvocation* di = dynamic_cast<Smp::IDynamicInvocation*>(model);
	assert(di);

	// Create request
	Smp::IRequest* req = di->CreateRequest(request->params().get<std::string>("operation").c_str());
	assert(req);

	// Collect paramters, if any
	if(req->GetParameterCount() > 0 )
	{
		// TODO: collect parameters
	}
	
	// Invoke request
	di->Invoke(req);

	// FIXME, pass to RPC response.
	Smp::AnySimple returnValue = req->GetReturnValue();

	di->DeleteRequest(req);

	return jsonrpcpp::Response (*request, "success");
}