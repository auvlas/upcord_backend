#include <QString>
#include <QSqlDatabase>
#include <QThread>
#include <QDebug>

#include "Database/Database.hpp"


namespace Database {
    Database::Database(QString prefixNameThread, QString typeDatabase,
            QString hostDatabase, QString nameDatabase,
            QString userNameDatabase, QString passwordDatabase)
        : m_prefixNameThread{prefixNameThread}, m_typeDatabase{typeDatabase},
        m_hostDatabase{hostDatabase}, m_nameDatabase{nameDatabase},
        m_userNameDatabase{userNameDatabase}, m_passwordDatabase{passwordDatabase} {}

    QSqlDatabase Database::getDatabaseConnection(void) {
        QString connectionName = (QString(m_prefixNameThread) + "_%1").arg((quintptr)QThread::currentThreadId());

        if (QSqlDatabase::contains(connectionName)) {
            return QSqlDatabase::database(connectionName);
        }

        QSqlDatabase db = QSqlDatabase::addDatabase(m_typeDatabase, connectionName);
        db.setHostName(m_hostDatabase);
        db.setDatabaseName(m_nameDatabase);
        db.setUserName(m_userNameDatabase);
        db.setPassword(m_passwordDatabase);
        
        if (!db.open()) {
            qDebug() << "Error open connection in the thread"
                << connectionName << ":" << db.lastError().text();
        }
        
        return db;
    }
}
