#pragma once

#include <stdexcept>


class PortUnavaliableException : public std::runtime_error {
public:
    PortUnavaliableException(void);
};
