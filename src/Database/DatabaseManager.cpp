#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QSqlDatabase>
#include <QSqlError>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <atomic>
#include <optional>

#include <Database/DatabaseManager.hpp>


namespace Database {
    DatabaseManager::DatabaseManager(QString prefixNameThread, QString typeDatabase,
                                     QString hostDatabase, QString nameDatabase,
                                     QString userNameDatabase, QString passwordDatabase,
                                     QObject *parent)
        : QObject(parent),
          m_prefixNameThread(prefixNameThread), m_typeDatabase(typeDatabase),
          m_hostDatabase(hostDatabase),         m_nameDatabase(nameDatabase),
          m_userNameDatabase(userNameDatabase), m_passwordDatabase(passwordDatabase)
    {
        QState *disconnectedState = new QState(&m_stateMachine);
        QState *connectingState   = new QState(&m_stateMachine);
        QState *connectedState    = new QState(&m_stateMachine);
        QState *errorState        = new QState(&m_stateMachine);

        disconnectedState->addTransition(this, &DatabaseManager::triggerConnect, connectingState);
        connectingState->  addTransition(this, &DatabaseManager::triggerSuccess, connectedState);
        connectingState->  addTransition(this, &DatabaseManager::triggerFailure, errorState);
        connectedState->   addTransition(this, &DatabaseManager::triggerLost,    errorState);
        errorState->       addTransition(this, &DatabaseManager::triggerConnect, connectingState);

        connect(connectingState, &QState::entered, this, &DatabaseManager::onConnectingEntered);
        connect(connectedState,  &QState::entered, this, &DatabaseManager::onConnectedEntered);
        connect(errorState,      &QState::entered, this, &DatabaseManager::onErrorEntered);

        m_stateMachine.setInitialState(disconnectedState);
        m_stateMachine.start();

        emit triggerConnect();
    }

    DatabaseManager::~DatabaseManager(void) {
        m_stateMachine.stop();
    }

    std::optional<QSqlDatabase> DatabaseManager::getConnection() {
        if (m_globalStatus.load(std::memory_order_relaxed) != DbStatus::Connected) {
            return std::nullopt; 
        }

        QString connectionName = QString("%1_%2").arg(m_prefixNameThread).arg((quintptr)QThread::currentThreadId());

        QMutexLocker locker(&m_dbMutex);

        if (QSqlDatabase::contains(connectionName)) {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            
            if (db.isOpen()) {
                return db; 
            }
        }

        QSqlDatabase db = QSqlDatabase::contains(connectionName) 
                          ? QSqlDatabase::database(connectionName)
                          : QSqlDatabase::addDatabase(m_typeDatabase, connectionName);

        db.setHostName(m_hostDatabase);
        db.setDatabaseName(m_nameDatabase);
        db.setUserName(m_userNameDatabase);
        db.setPassword(m_passwordDatabase);

        if (!db.open()) {
            qDebug() << "[Thread" << QThread::currentThreadId() << "] Failed to open DB:" << db.lastError().text();
            
            emit triggerLost(); 
            return std::nullopt;
        }

        qDebug() << "[Thread" << QThread::currentThreadId() << "] Connection authorized and cached.";
        return db;
    }

    bool DatabaseManager::isReady(void) {
        return m_globalStatus.load(std::memory_order_relaxed) == DbStatus::Connected;
    }

    void DatabaseManager::onConnectingEntered(void) {
        m_globalStatus.store(DbStatus::Connecting, std::memory_order_relaxed);
        qDebug() << "[State Machine] Connecting to database master server...";

        QString masterConnName = QString("%1_master").arg(m_prefixNameThread);
        QSqlDatabase db = QSqlDatabase::contains(masterConnName) 
                          ? QSqlDatabase::database(masterConnName)
                          : QSqlDatabase::addDatabase(m_typeDatabase, masterConnName);
        
        db.setHostName(m_hostDatabase);
        db.setDatabaseName(m_nameDatabase);
        db.setUserName(m_userNameDatabase);
        db.setPassword(m_passwordDatabase);

        if (db.open()) {
            emit triggerSuccess();
        } else {
            qDebug() << "[State Machine] Master connection failed:" << db.lastError().text();
            emit triggerFailure();
        }
    }

    void DatabaseManager::onConnectedEntered(void) {
        m_globalStatus.store(DbStatus::Connected, std::memory_order_relaxed);
        qDebug() << "[State Machine] DATABASE READY. All threads unblocked.";
    }

    void DatabaseManager::onErrorEntered(void) {
        m_globalStatus.store(DbStatus::Error, std::memory_order_relaxed);
        qDebug() << "[State Machine] Critical Error State. Reconnecting in 5 seconds...";
        
        QTimer::singleShot(5000, this, [this]() {
            emit triggerConnect();
        });
    }
}
