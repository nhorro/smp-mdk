cmake_minimum_required(VERSION 3.10)

find_package(Boost COMPONENTS system filesystem REQUIRED)

# set the project name
project(managed_counter_example)

# add the executable
add_executable(${PROJECT_NAME}
    main.cpp 
    ManagedCounter.cpp
    CounterClass.cpp
    ${LIBSMP2_SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    pthread
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../../libsmp2/
        ../../thirdparty/
)