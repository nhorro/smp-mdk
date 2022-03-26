#ifndef SIMULATOR_SERVICE_H
#define SIMULATOR_SERVICE_H

#include <boost/format.hpp>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"
#include "Smp/IEntryPoint.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/IDynamicInvocation.h"

#include "Mdk/Model.h"
#include "Mdk/Object.h"

#include "DynamicLoader.h"
#include "rpc/jsonrpc_server.hpp"
#include "rpc/transport/implementation/zmq_reqrep_transport.hpp"


class SimulatorService
{
public:
	SimulatorService(int rpc_port, int rpc_timeout_ms, const std::string& config);
	~SimulatorService();
	void registerRPCMethods();
	void setupAndStart();
	void cleanupAndShutdown();
private:
	std::shared_ptr<rpc_transport_base> rpc_transport;
	jsonrpc_server server;
	const std::string m_configFilename;
	Smp::Simulator m_sim;
	DynamicLoader m_dl;

	/* RPC Methods */

	// Just a test.
	jsonrpcpp::Response rpc_hello(jsonrpcpp::request_ptr request)
	{
		return jsonrpcpp::Response (
			*request, 
			(boost::format("Hello, %s.") %  request->params().get<std::string>("name")).str()
		);			
	}

	jsonrpcpp::Response rpc_model_request(jsonrpcpp::request_ptr request);
};

#endif // SIMULATOR_SERVICE_H