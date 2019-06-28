##########################################################################################
cmake_minimum_required (VERSION 3.10)

##########################################################################################
project (Boggle VERSION 1.0.0.0 LANGUAGES CXX)

option(BUILD_TESTING "Setting build type to debug build" ON )

# Specify build option to only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Limited configurations" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)	

#disable exceptions
if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
	string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()
#use /W4
string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${EXECUTABLE_OUTPUT_PATH})

add_definitions(-D_HAS_EXCEPTIONS=0)
add_subdirectory(source)



