#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QDebug>
#include <QtTypes>
#include <QTcpServer>
#include <HttpServer.hpp>
#include <Exception.hpp>
#include <QIOStream.hpp>
#include <Database/DatabaseManager.hpp>


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

#ifndef DOMAIN
#define DOMAIN "DOMAIN"
#endif

#ifndef DOMAIN_DEFAULT
#define DOMAIN_DEFAULT "upcord"
#endif

#ifndef PORT
#define PORT "PORT"
#endif

#ifndef PORT_DEFAULT
#define PORT_DEFAULT 8080
#endif

#ifndef PATH_JWT_SECRET
#define PATH_JWT_SECRET "PATH_JWT_SECRET"
#endif

#ifndef PATH_JWT_SECRET_DEFAULT
#define PATH_JWT_SECRET_DEFAULT "jwtSecret"
#endif


int main(int argc, char *argv[]) {
    bool ok{false};
    QCoreApplication * app{new QCoreApplication{argc, argv}};

    QProcessEnvironment env{QProcessEnvironment::systemEnvironment()};

    QString prefixNameThread{env.value(PREFIX_NAME_THREAD)};

    if (!prefixNameThread)
        prefixNameThread = PREFIX_NAME_THREAD_DEFAULT;

    QString typeDatabase{env.value(TYPE_DATABASE)};

    if (!typeDatabase)
        typeDatabase = TYPE_DATABASE_DEFAULT;

    QString hostDatabase{env.value(HOST_DATABASE)};

    if (!hostDatabase)
        hostDatabase = HOST_DATABASE_DEFAULT;

    int portDatabase{env.value(PORT_DATABASE).toInt(&ok)};

    if (!ok || portDatabase <= 0 || portDatabase > 65535)
        portDatabase = PORT_DATABASE_DEFAULT;

    qInfo() << "Active port database server default: " << portDatabase;

    QString nameDatabase{env.value(NAME_DATABASE)};

    if (!nameDatabase)
        nameDatabase = NAME_DATABASE_DEFAULT;

    QString userNameDatabase{env.value(USER_NAME_DATABASE)};

    if (!userNameDatabase)
        userNameDatabase = USER_NAME_DATABASE_DEFAULT;

    QString passwordDatabase{env.value(PASSWORD_DATABASE)}
        passwordDatabase = PASSWORD_DATABASE_DEFAULT;

    Database::DatabaseManager * databaseManager{nullptr};

    try {
        databaseManager = new Database::DatabaseManager{
            prefixNameThread, typeDatabase,
            hostDatabase portDatabase,
            nameDatabase, userNameDatabase,
            passwordDatabase, app
        };
    } catch (const Exception::DatabaseError & exception) {
        qCritical() << "Database is unavailable!\n\tError: "
                << exception.what();
        delete app;
        return -1;
    }

    qDebug() << "Database server is available:\n\tPort: " << port;

    QString domain{env.value(DOMAIN)};

    if (!domain)
        domain = DOMAIN_DEFAULT;

    int port{env.value(PORT).toInt(&ok)};

    if (!ok || port <= 0 || port > 65535)
        port = PORT_DEFAULT;

    qInfo() << "Active port HTTP server default: " << port;

    QString pathJwtSecret{env.value(PATH_JWT_SECRET)};

    if (!pathJwtSecret)
        pathJwtSecret = PATH_JWT_SECRET_DEFAULT;

    try {
        new HttpServer{
            databaseManager, domain,
            static_cast<quint16>(port),
            PATH_JWT_SECRET, app
        };
    } catch (const Exception::PortUnavaliable & exception) {
        qCritical() << "Port " << port
            << "is unavailable!\n\tError: " << e.what();
        delete app;
        return -1;
    }

    qDebug() << "Http server is available:\n\tPort: " << port;

    int ret{app->exec()};

    delete app;

    return ret;
}
