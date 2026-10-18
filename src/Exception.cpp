#include <stdexcept>
#include <QSqlError>
#include <QString>

#include <Exception.hpp>


namespace Exception {
    PortUnavaliable::PortUnavaliable(void) 
            : std::runtime_error("Port is unavailable") {}

    DatabaseError::DatabaseError(QSqlError error)
            : std::runtime_error(error.text().toStdString()) {}
}
