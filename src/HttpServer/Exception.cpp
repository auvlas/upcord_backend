#include <stdexcept>

#include <HttpServer/Exception.hpp>


namespace HttpServer {
    namespace Exception {
        PortUnavaliableException::PortUnavaliableException() 
                : std::runtime_error("Port is unavailable") { }
    }
}
