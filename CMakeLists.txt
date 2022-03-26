cmake_minimum_required(VERSION 3.10)

# set the project name
project(smp-mdk)

# FIXME 
set( LIBSMP2_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Management/EntryPointPublisher.cpp
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Management/EventConsumer.cpp
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Management/EventProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Management/ManagedComponent.cpp
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Management/ManagedObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Aggregate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/AnySimple.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Component.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Composite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/DateTime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Duration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Mdk/Uuid.cpp

    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Publication/Publication.cpp

	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Services/Service.cpp
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Services/Logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Services/Scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Services/TimeKeeper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Services/EventManager.cpp    
	${CMAKE_CURRENT_LIST_DIR}/libsmp2/Smp/Simulator.cpp
)

add_subdirectory(libsmp2)
add_subdirectory(examples)
add_subdirectory(models)
add_subdirectory(simulator)
add_subdirectory(tests)