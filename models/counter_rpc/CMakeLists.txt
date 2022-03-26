cmake_minimum_required(VERSION 3.10)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package (yaml-cpp)

# set the project name
project(counter_rpc)

# add the executable
add_library(${PROJECT_NAME} SHARED
    CounterRPC.cpp
    CounterResetRequest.cpp
    ${LIBSMP2_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    pthread    
    #yaml-cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../../libsmp2/
        ../../thirdparty/
)