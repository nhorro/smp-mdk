
#ifndef SMP_SIMULATOR_H
#define SMP_SIMULATOR_H

#include "Smp/ISimulator.h"
#include "Mdk/Composite.h"
#include "Mdk/Component.h"

#include "Smp/Services/Logger.h"
#include "Smp/Services/Scheduler.h"
#include "Smp/Services/TimeKeeper.h"
#include "Smp/Services/EventManager.h"

#include "Smp/Publication/Publication.h"

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/format.hpp>

namespace Smp
{
    class Simulator :
        public ISimulator, 
        public Mdk::Composite,
        public Mdk::Component
    {
    public:
        Simulator();
    
        ~Simulator();

        /// Get all models.
        /// Query for the collection of all root models.
        /// @return Collection of root model components.
        /// @remarks The collection may be empty if no models exist
        ///          in the Models container.
        const ModelCollection* GetModels();

        /// Get a root model by name.
        /// Query for a root model by its name.
        /// @param   name Model name.
        /// @return  Root model with the given name, or null if no 
        ///          root model with the given name could be found.
        /// @remarks Users should always check the return value, as null
        ///          is returned when no root model with the given name
        ///          could be found.
        IModel* GetModel(String8 name);

        /// Add a root model.
        /// Add a new root model to the simulator.
        /// @param   model The root model.
        /// @remarks As root models are identified by their name, the new model
        ///          needs to have a unique name within the root models.
        ///          Otherwise, it will not be added, and an exception of type
        ///          DuplicateName will be raised.
        void AddModel(IModel* model);

        /// Get all services.
        /// Query for the collection of all services.
        /// @return Collection of services.
        /// @remarks The collection may be empty if no services exist
        ///          in the Services container.
        const ServiceCollection* GetServices();

        /// Get a service by name.
        /// Query for a service by its name.
        /// @param   name Service name.
        /// @return  Service with the given name, or null if no 
        ///          service with the given name could be found.
        /// @remarks Users should always check the return value, as null
        ///          is returned when no service with the given name
        ///          could be found.
        IService* GetService(String8 name);

        /// Add a user-defined service.
        /// Add a new service to the simulator.
        /// @param   service The user-defined service.
        /// @remarks As services are identified by their name, the new service
        ///          needs to have a unique name within the services.
        ///          Otherwise, it will not be added, and an exception of type
        ///          DuplicateName will be raised.
        void AddService(IService* service);

        /// Get logger service.
        /// Query for mandatory logger service.
        /// @return  Mandatory logger service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          logger service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        Services::ILogger* GetLogger() const;

        /// Get scheduler service.
        /// Query for mandatory scheduler service.
        /// @return  Mandatory scheduler service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          scheduler service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        Services::IScheduler* GetScheduler() const;

        /// Get time keeper service.
        /// Query for mandatory time keeper service.
        /// @return  Mandatory time keeper service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          time keeper service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        Services::ITimeKeeper* GetTimeKeeper() const;

        /// Get event manager service.
        /// Query for mandatory event manager service.
        /// @return  Mandatory event manager service.
        /// @remarks This is a type-safe convenience method to query for the
        ///          event manager service, to avoid having to use the general
        ///          GetService() method. For the mandatory services, it is 
        ///          recommended to use the convenience methods.
        Services::IEventManager* GetEventManager() const;

        /// Get simulator state.
        /// Returns the current simulator state.
        /// @return  Current simulator state.
        SimulatorStateKind GetState() const;

        /// Call Publish() method of models.
        /// This method asks the simulation environment to call the Publish()
        /// method of all model instance in the hierarchy which are still in
        /// <em>Created</em> state.
        /// @remarks This method is typically called by an external component
        ///          after creating new model instances.
        void Publish();

        /// Call Configure() method of models.
        /// This method asks the simulation environment to call the Configure()
        /// method of all model instance in the hierarchy which are still in
        /// <em>Publishing</em> state.
        /// @remarks This method is typically called by an external component
        ///          after setting field values of new model instances,
        ///          typically using the information in an SMDL Assembly.
        ///          This method can only be called in Building state.
        void Configure();

        /// Enter Connecting state.
        /// This method informs the simulation environment that the hierarchy
        /// of model instances has been built, and can now be connected
        /// to the simulator. After connecting all models, an automatic state
        /// transition to the Initialising state is performed.
        /// @remarks This method is typically called by an external component
        ///          after creating and configuring all model instances.
        void Connect();

        /// Enter initialising state.
        /// This method changes from Standby state to Initialising state,
        /// where each initialisation entry point will be executed again.
        /// @remarks The entry points will be called in the order they
        ///          have been added using the AddInitEntryPoint() method.
        void Initialise();

        /// Enter standby state.
        /// This method changes from executing to standby state.
        /// @remarks This method can only be called when in Executing state.
        void Hold();

        /// Enter executing state.
        /// This method changes from standby to executing state.
        /// @remarks This method can only be called when in Standby state.
        void Run();

        /// Enter storing state.
        /// This method is used to store a state vector to file.
        /// @param   filename Name to use for simulation state vector file.
        /// @remarks This method can only be called when in Standby state.
        void Store(String8 filename);

        /// Enter restoring state.
        /// This method is used to restore a state vector from file.
        /// @param   filename Name of simulation state vector file.
        /// @remarks This method can only be called when in Standby state.
        void Restore(String8 filename);

        /// Enter exiting state.
        /// This method is used for a normal termination of a simulation.
        /// @remarks This method can only be called when in Standby state.
        void Exit();

        /// Enter aborting state.
        /// This method is used for an abnormal termination of a simulation.
        /// @remarks This method can be called from any other state.
        void Abort();

        /// Add initialisation entry point.
        /// This method can be used to add entry points that shall be executed
        /// in the Initialising state.
        /// These entry points will be called in the order they have been
        /// added to the simulator using this method.
        /// @par
        /// The ITask interface (which is derived from IEntryPoint) can be 
        /// used to add several entry points in a well-defined order.
        void AddInitEntryPoint(IEntryPoint* entryPoint);

    private:
        std::atomic<SimulatorStateKind> m_state;

        Smp::Services::ILogger* m_logger;
        Services::IScheduler* m_scheduler;
        Services::ITimeKeeper* m_timeKeeper;
        Services::IEventManager* m_eventManager;

        IPublication* m_publication;

        ModelCollection m_models;

        // Hold a dictionary of models. 
        // FIXME: use a better method for this.
        std::map<std::string,Smp::IModel*> m_modelsDict;
    };
}

#endif // SMP_SIMULATOR_H