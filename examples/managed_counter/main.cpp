#include <iostream>
#include <boost/format.hpp>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"


#include "Smp/IEntryPoint.h"
#include "Smp/Services/IScheduler.h"
#include "Mdk/Object.h"
#include "ManagedCounter.h"

int main(int argc,const char* argv[])
{
	try {
		// Instance a simulator
		Smp::Simulator sim;
	
		// Access services from simulator	
		sim.GetLogger()->Log(nullptr,"Simulation started", Smp::Services::LMK_Information);

		// 1. Create models
		sim.GetLogger()->Log(nullptr,"Creating models", Smp::Services::LMK_Information);

		ManagedCounter counter("counter", &sim);
		sim.AddModel(&counter);

		// Publish variables in the simulation environment
		sim.GetLogger()->Log(nullptr,"Publishing model variables", Smp::Services::LMK_Information);
		sim.Publish();

		// Configure
		sim.GetLogger()->Log(nullptr,"Configuring models", Smp::Services::LMK_Information);
		sim.Configure();

		// Connect
		sim.GetLogger()->Log(nullptr,"Connecting models", Smp::Services::LMK_Information);
    	sim.Connect();

		// Initialize
		sim.GetLogger()->Log(nullptr,"Initializing models", Smp::Services::LMK_Information);
		sim.Initialise();

		// Run simulation
		sim.GetLogger()->Log(nullptr,"Running simulation", Smp::Services::LMK_Information);
    	sim.Run();

		std::cout << "Press any key to stop" << std::endl;
		std::getchar();
		
		sim.GetLogger()->Log(nullptr,"Holding simulation", Smp::Services::LMK_Information);
		sim.Hold();

		// Exit simulation
		sim.GetLogger()->Log(nullptr,"Leaving simulation", Smp::Services::LMK_Information);
		sim.Exit();
	} 
	catch(const Smp::Exception& ex)
	{		
		std::cerr << "Exception " << ex.GetName() << ". " 
		          << ex.GetDescription() << std::endl
				  << "Cause: " << ex.what() << std::endl;
	}

	return 0;
}