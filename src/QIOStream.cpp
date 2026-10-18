#include <QTextStream>

#include <QIOStream.hpp>


namespace std {
    QTextStream qin{stdin};
    QTextStream qout{stdout};
}
