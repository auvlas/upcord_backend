#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QDebug>
#include <QtTypes>
#include <QTcpServer>
#include <requests/HttpServer.hpp>
#include <requests/PortUnavaliableException.hpp>

#ifndef PORT
#define PORT "PORT"
#endif

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 8080
#endif

int main(int argc, char *argv[]) {
    QCoreApplication * app{new QCoreApplication{argc, argv}};

    QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};

    bool ok{false};
    int portEnv{env.value(PORT).toInt(&ok)};

    if (!ok || portEnv <= 0 || portEnv > 65535) {
        portEnv = DEFAULT_PORT;
        qInfo() << "Active port default: " << portEnv;
    }

    quint16 port(portEnv);

    HttpServer * httpServer{nullptr};

    try {
        httpServer = new HttpServer{port, app};
    } catch (const PortUnavaliableException & e) {
        qCritical() << "Port " << port << "is unavailable!\n\tError: " << e.what();
        delete app;
        return -1;
    }

    qDebug() << "HttpServer is available:\n\tPort: " << port;

    int ret{app->exec()};

    delete app;

    return ret;
}
