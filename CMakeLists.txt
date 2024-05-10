cmake_minimum_required(VERSION 3.10)
project(PetWebService)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package(Boost 1.65.0 REQUIRED COMPONENTS system date_time)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(PetWebService main.cpp
        Persistence/MemCache.cpp
        Persistence/MemCache.h
        DataEntity/Pet.h
        HttpHandler/RequestHandler.cpp
        HttpHandler/RequestHandler.h
        Util/RequestHandlerThread.h
        Util/RequestHandlerThread.cpp)
target_link_libraries(PetWebService ${Boost_LIBRARIES})