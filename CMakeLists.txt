cmake_minimum_required(VERSION 3.25) 
project(Upcord VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core HttpServer)

find_package(OpenSSL REQUIRED)

include(FetchContent)
FetchContent_Declare(
    jwt-cpp
    GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
    GIT_TAG        v0.7.2
)
FetchContent_MakeAvailable(jwt-cpp)

add_executable(Upcord
    src/requests/PortUnavaliableException.hpp
    src/requests/PortUnavaliableException.cpp
    src/requests/HttpServer.hpp
    src/requests/HttpServer.cpp
    src/main.cpp
)

set(ENV_PORT_NAME "UPCORD_PORT"
    CACHE STRING "Name of the environment variable for server port"
)

set(ENV_DEFAULT_PORT "3000"
    CACHE STRING "Name of the environment variable for server port"
)

target_compile_options(jwt-cpp INTERFACE -Wno-deprecated-declarations)
target_compile_definitions(Upcord PRIVATE PORT=\"${ENV_PORT_NAME}\")
target_compile_definitions(Upcord PRIVATE DEFAULT_PORT=${ENV_DEFAULT_PORT})
target_include_directories(Upcord PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Upcord PRIVATE
    Qt6::Core
    Qt6::HttpServer
    OpenSSL::SSL
    OpenSSL::Crypto
    jwt-cpp::jwt-cpp
)
