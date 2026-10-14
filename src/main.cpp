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

#ifndef PORT_DEFAULT
#define PORT_DEFAULT 8080
#endif

#ifndef DOMAIN
#define DOMAIN "DOMAIN"
#endif

#ifndef DOMAIN_DEFAULT
#define DOMAIN_DEFAULT "upcord"
#endif

#ifndef PATH_JWT_SECRET
#define PATH_JWT_SECRET "PATH_JWT_SECRET"
#endif

#ifndef PATH_JWT_SECRET_DEFAULT
#define PATH_JWT_SECRET_DEFAULT "jwtSecret"
#endif

#ifndef PREFIX_NAME_THREAD
#define PREFIX_NAME_THREAD "PREFIX_NAME_THREAD"
#endif

#ifndef PREFIX_NAME_THREAD_DEFAULT
#define PREFIX_NAME_THREAD_DEFAULT "connection"
#endif

#ifndef TYPE_DATABASE
#define TYPE_DATABASE "TYPE_DATABASE"
#endif

#ifndef TYPE_DATABASE_DEFAULT
#define TYPE_DATABASE_DEFAULT "QPSQL"
#endif

#ifndef HOST_DATABASE
#define HOST_DATABASE "HOST_DATABASE"
#endif

#ifndef HOST_DATABASE_DEFAULT
#define HOST_DATABASE_DEFAULT "127.0.0.1"
#endif

#ifndef PORT_DATABASE
#define PORT_DATABASE "PORT_DATABASE"
#endif

#ifndef PORT_DATABASE_DEFAULT
#define PORT_DATABASE_DEFAULT 5432
#endif

#ifndef NAME_DATABASE
#define NAME_DATABASE "NAME_DATABASE"
#endif

#ifndef NAME_DATABASE_DEFAULT
#define NAME_DATABASE_DEFAULT "postgress"
#endif

#ifndef USER_NAME_DATABASE
#define USER_NAME_DATABASE "USER_NAME_DATABASE"
#endif

#ifndef USER_NAME_DATABASE_DEFAULT
#define USER_NAME_DATABASE_DEFAULT "postgress"
#endif

#ifndef PASSWORD_DATABASE_DEFAULT
#define PASSWORD_DATABASE_DEFAULT "1234"
#endif


int main(int argc, char *argv[]) {
    bool ok{false};
    QCoreApplication * app{new QCoreApplication{argc, argv}};

    QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};

    int portDatabaseServer{env.value(PORT_DATABASE).toInt(&ok)};

    if (!ok || portDatabaseServer <= 0 || portDatabaseServer > 65535)
        portDatabaseServer = PORT_DATABASE_DEFAULT;

    qInfo() << "Active port database server default: " << portDatabaseServer;

    Database::DatabaseManager * databaseManager{
        new Database::DatabaseManager{
            PREFIX_NAME_THREAD_DEFAULT,
            TYPE_DATABASE_DEFAULT,
            HOST_DATABASE_DEFAULT,
            portDatabaseServer,
            NAME_DATABASE_DEFAULT,
            USER_NAME_DATABASE_DEFAULT,
            PASSWORD_DATABASE_DEFAULT,
            app
        }
    };

    qDebug() << "Database server is available:\n\tPort: " << portDatabaseServer;

    int portHttpServer{env.value(PORT).toInt(&ok)};

    if (!ok || portHttpServer <= 0 || portHttpServer > 65535)
        portHttpServer = PORT_DEFAULT;

    qInfo() << "Active port HTTP server default: " << portHttpServer;

    HttpServer::HttpServer * httpServer{nullptr};

    try {
        HttpServer::HttpServer * httpServer{
            new HttpServer::HttpServer{
                DOMAIN, PATH_JWT_SECRET, databaseManager, static_cast<quint16>(portHttpServer), app
            }
        };
    } catch (const HttpServer::Exception::PortUnavaliableException & e) {
        qCritical() << "Port " << portHttpServer << "is unavailable!\n\tError: " << e.what();
        delete app;
        return -1;
    }

    qDebug() << "Http server is available:\n\tPort: " << portHttpServer;

    int ret{app->exec()};

    delete app;

    return ret;
}
