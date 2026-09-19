#pragma once

#include <stdexcept>


namespace HttpServer {
    namespace Exception {
        class PortUnavaliableException : public std::runtime_error {
        public:
            PortUnavaliableException(void);
        };
    }
}
