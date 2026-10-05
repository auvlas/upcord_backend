#pragma once

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QSqlDatabase>
#include <QSqlError>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <atomic>
#include <optional>


namespace Database {
    class DatabaseManager : public QObject {
        Q_OBJECT

    private:
        enum class DbStatus {
            Disconnected,
            Connecting,
            Connected,
            Error
        };

        const QString m_prefixNameThread;
        const QString m_typeDatabase;
        const QString m_hostDatabase;
        const int     m_portDatabase;
        const QString m_nameDatabase;
        const QString m_userNameDatabase;
        const QString m_passwordDatabase;
        std::atomic<DbStatus> m_globalStatus{
            DbStatus::Disconnected
        };
        QStateMachine m_stateMachine;
        QMutex m_dbMutex;

    public:
        DatabaseManager(QString prefixNameThread, QString typeDatabase,
                        QString hostDatabase,     int portDatabase,
                        QString nameDatabase,     QString userNameDatabase,
                        QString passwordDatabase, QObject *parent = nullptr);
        
        ~DatabaseManager(void);

        QSqlDatabase getConnection(void);

        bool isReady(void) const;

        explicit operator bool() {

        }

    signals:
        void triggerConnect(void);
        void triggerSuccess(void);
        void triggerFailure(void);
        void triggerLost(void);

    private slots:
        void onConnectingEntered(void);
        void onConnectedEntered(void);
        void onErrorEntered(void);
    };
}
