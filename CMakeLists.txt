find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

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

set(JWT_BUILD_EXAMPLES OFF CACHE INTERNAL "Disable jwt-cpp examples" FORCE)

FetchContent_MakeAvailable(jwt-cpp)


FetchContent_Declare(
    snowflake-cpp
    GIT_REPOSITORY https://github.com/sniper00/snowflake-cpp.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(snowflake-cpp)


add_link_options("-fuse-ld=mold")


add_executable(Upcord
    src/HttpServer/Exception.hpp
    src/HttpServer/Exception.cpp
    src/HttpServer/HttpServer.hpp
    src/HttpServer/HttpServer.cpp
    src/HttpServer/Secret.hpp
    src/HttpServer/Secret.cpp
    src/main.cpp
)


target_precompile_headers(Upcord PRIVATE
    <QObject>
    <QCoreApplication>
    <QHttpServer>
    <QJsonObject>
    <QHttpServerResponse>
    <QDateTime>
    <QTcpServer>
    <QtTypes>
    <QString>
    <QByteArray>
    <QRandomGenerator>
    <QHttpServerRequest>
    <QDebug>
    <QTextStream>
    <QFile>
    <QFileInfo>
    <QPasswordDigestor>
    <QHttpHeaders>
    <stdexcept>
    <string>
    <jwt-cpp/jwt.h>
    <snowflake.hpp>
    <HttpServer/Exception.hpp>
    <HttpServer/HttpServer.hpp>
    <HttpServer/Secret.hpp>
)


set(ENV_PORT_NAME "UPCORD_PORT"
    CACHE STRING "Name of the environment variable for server port"
)

set(ENV_DEFAULT_PORT "3000"
    CACHE STRING "Default port"
)

set(ENV_PATH_JWT_SECRET ".upcordJwtSecret"
    CACHE STRING "Path JWT secret"
)

set(ENV_DOMAIN "localhost:8080"
    CACHE STRING "Domain website"
)


target_compile_definitions(Upcord PRIVATE
    PORT=\"${ENV_PORT_NAME}\"
    DEFAULT_PORT=${ENV_DEFAULT_PORT}
    DOMAIN=\"${ENV_DOMAIN}\"
    PATH_JWT_SECRET=\"${ENV_PATH_JWT_SECRET}\"

)


target_compile_options(jwt-cpp INTERFACE -Wno-deprecated-declarations)


target_include_directories(Upcord SYSTEM PRIVATE ${snowflake-cpp_SOURCE_DIR})

target_include_directories(Upcord PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


target_link_libraries(Upcord PRIVATE
    Qt6::Core
    Qt6::HttpServer
    OpenSSL::SSL
    OpenSSL::Crypto
    jwt-cpp::jwt-cpp
)
