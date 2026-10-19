#pragma once

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <atomic>
#include <expected>
#include <optional>


namespace Database {
    class Manager : public QObject {
        Q_OBJECT

    private:
        QSqlDatabase           m_main;
        QStateMachine          m_stateMachine;
        QMutex                 m_lock;
        QState *               m_connected;

    public:
        Manager(
                QString prefixNameThread, QString   type,
                QString host,             int       port,
                QString name,             QString   userName,
                QString password,         QObject * parent = nullptr);
        ~Manager(void);

    private:
        QString connectionName(void) const;
        QSqlDatabase connect(void);

    public:
        std::expected<QSqlDatabase, QSqlError> getConnection(void);
        operator bool(void) const;
        bool isReady(void) const;

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
