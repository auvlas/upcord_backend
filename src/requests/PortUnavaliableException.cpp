#include <stdexcept>

#include <requests/PortUnavaliableException.hpp>


PortUnavaliableException::PortUnavaliableException() 
        : std::runtime_error("Port is unavailable") { }
