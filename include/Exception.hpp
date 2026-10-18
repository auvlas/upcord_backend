#pragma once

#include <stdexcept>
#include <QSqlError>


namespace Exception {
    class PortUnavaliableException : public std::runtime_error {
    public:
        PortUnavaliableException(void);
    };

    class DatabaseError : public std::runtime_error {
    public:
        DatabaseError(QSqlError error);
    };
}
