#pragma once

#include <QString>
#include <QSqlDatabase>

namespace Database {
    class Database {
    private:
        QString m_prefixNameThread{};
        QString m_typeDatabase{};
        QString m_hostDatabase{};
        QString m_nameDatabase{};
        QString m_userNameDatabase{};
        QString m_passwordDatabase{};

    public:
        Datbase(QString prefixNameThread, QString typeDatabase,
                QString hostDatabase, QString nameDatabase,
                QString userNameDatabase, QString passwordDatabase);

        QSqlDatabase getDatabaseConnection(void);
    };
}
