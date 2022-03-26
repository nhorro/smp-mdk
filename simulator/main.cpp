#include <iostream>
#include <string>

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include "SimulatorService.h"

int run_simulation_service(const boost::program_options::variables_map& vm)
{
	try 
	{
		int rpc_port = vm["rpc_port"].as<int>();
		int rpc_timeout = 500; // milliseconds
		
		SimulatorService sim(rpc_port,rpc_timeout,vm["config"].as<std::string>());
		
		sim.setupAndStart();

		std::cout << "Receiving commands at port " << rpc_port << ". Press any key to stop service.";
		std::getchar();

		sim.cleanupAndShutdown();
	} 
	catch(const Smp::Exception& ex)
	{		
		std::cerr << "Exception " << ex.GetName() << ". " 
				<< ex.GetDescription() << std::endl
				<< "Cause: " << ex.what() << std::endl;
	} 
	catch ( const rpc_transport_base::exception& tex )
	{
		std::cerr << "Server communication exception: " << tex.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "Unhandled exception" << std::endl;
	}

	std::cout << "Application finished gracefully." << std::endl;
	return 0;
}


int main(int argc,const char* argv[])
{
	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
    	("help", "this help")
		("rpc_port", po::value<int>()->default_value(5050)->required(), "RPC port")
    	("config", po::value<std::string>()->required(), "configuration file");
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    
	
	if (vm.count("help")) 
	{
    	std::cout << desc << "\n";
    	return 1;
	}

	return run_simulation_service(vm);	
	//return test_load_yaml(vm);
}