set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(smp2  ${LIBSMP2_SOURCES} )

target_include_directories(smp2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ../thirdparty/
)

install(TARGETS smp2 DESTINATION lib)

install(DIRECTORY Smp
        DESTINATION include        
)

install(DIRECTORY Smp
        DESTINATION include 
        FILES_MATCHING 
        PATTERN "Mdk/*.h" 
)