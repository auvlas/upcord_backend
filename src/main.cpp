#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QDebug>
#include <QtTypes>
#include <QTcpServer>
#include <HttpServer/HttpServer.hpp>
#include <HttpServer/Exception.hpp>
#include <Database/DatabaseManager.hpp>

#ifndef PORT
#define PORT "PORT"
#endif

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 8080
#endif

#ifndef DOMAIN
#define DOMAIN "localhost:4000"
#endif

#ifndef PATH_JWT_SECRET
#define PATH_JWT_SECRET "jwtSecret"
#endif

#ifndef PREFIX_NAME_THREAD_DEFAULT
#define PREFIX_NAME_THREAD_DEFAULT "connection"
#endif

#ifndef TYPE_DATABASE_DEFAULT
#define TYPE_DATABASE_DEFAULT "QPSQL"
#endif

#ifndef HOST_DATABASE_DEFAULT
#define HOST_DATABASE_DEFAULT "127.0.0.1"
#endif

#ifndef NAME_DATABASE_DEFAULT
#define NAME_DATABASE_DEFAULT "5432"
#endif

#ifndef USER_NAME_DATABASE_DEFAULT
#define USER_NAME_DATABASE_DEFAULT "postgress"
#endif

#ifndef PASSWORD_DATABASE_DEFAULT
#define PASSWORD_DATABASE_DEFAULT "1234"
#endif


int main(int argc, char *argv[]) {
    QCoreApplication * app{new QCoreApplication{argc, argv}};

    QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};

    Database::DatabaseManager * databaseManager{
        new Database::DatabaseManager{
            PREFIX_NAME_THREAD_DEFAULT,
            TYPE_DATABASE_DEFAULT,
            HOST_DATABASE_DEFAULT,
            NAME_DATABASE_DEFAULT,
            USER_NAME_DATABASE_DEFAULT,
            PASSWORD_DATABASE_DEFAULT,
            app
        }
    }

    bool ok{false};
    int portEnv{env.value(PORT).toInt(&ok)};

    if (!ok || portEnv <= 0 || portEnv > 65535) {
        portEnv = DEFAULT_PORT;
        qInfo() << "Active port default: " << portEnv;
    }

    quint16 port(portEnv);

    HttpServer::HttpServer * httpServer{nullptr};

    try {
        httpServer = new HttpServer::HttpServer{
            DOMAIN, PATH_JWT_SECRET, port, databaseManager, app
        };
    } catch (const HttpServer::Exception::PortUnavaliableException & e) {
        qCritical() << "Port " << port << "is unavailable!\n\tError: " << e.what();
        delete app;
        return -1;
    }

    qDebug() << "HttpServer is available:\n\tPort: " << port;

    int ret{app->exec()};

    delete app;

    return ret;
}
