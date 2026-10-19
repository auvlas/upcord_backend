#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QtTypes>
#include <atomic>
#include <expected>
#include <Exception.hpp>

#include <Database/DatabaseManager.hpp>


namespace Database {
    Manager::Manager(
            QString prefixNameThread, QString   type,
            QString host,             int       port,
            QString name,             QString   userName,
            QString password,         QObject * parent)
        : QObject{parent},m_prefixNameThread{prefixNameThread} {
        QString name{connectionName()};
        QSqlDatabase db{QSqlDatabase::addDatabase(type, name)};

        db.setHostName(host);
        db.setPort(port);
        db.setDatabaseName(name);
        db.setUserName(userName);
        db.setPassword(password);

        if (db.open())
            m_main = db;
        else if (db.lastError().isValid())
            throw DatabaseError{db.lastError()}

        QState *disconnectedState = new QState(&m_stateMachine);
        QState *connectingState   = new QState(&m_stateMachine);
        QState *connectedState    = new QState(&m_stateMachine);
        QState *errorState        = new QState(&m_stateMachine);

        m_connected = connectedState;

        disconnectedState->addTransition(this,
                &DatabaseManager::triggerConnect, connectingState);
        connectingState->  addTransition(this,
                &DatabaseManager::triggerSuccess, connectedState);
        connectingState->  addTransition(this,
                &DatabaseManager::triggerFailure, errorState);
        connectedState->   addTransition(this,
                &DatabaseManager::triggerLost,    errorState);
        errorState->       addTransition(this,
                &DatabaseManager::triggerConnect, connectingState);

        connect(connectingState, &QState::entered, this,
                &DatabaseManager::onConnectingEntered);
        connect(connectedState,  &QState::entered, this,
                &DatabaseManager::onConnectedEntered);
        connect(errorState,      &QState::entered, this,
                &DatabaseManager::onErrorEntered);

        m_stateMachine.setInitialState(disconnectedState);
        m_stateMachine.start();

        emit triggerConnect();
    }

    Manager::~Manager(void) {
        m_stateMachine.stop();
    }

    QString Manager::connectionName(void) const {
        return QString{"%1_%2"}.arg(m_prefixNameThread)
                .arg((quintptr)QThread::currentThreadId());
    }

    QSqlDatabase Manager::connect(void) {
        QString name{connectionName()};

        m_lock.lock();

        if (QSqlDatabase::contains(name))
            return QSqlDatabase::database(name);

        QSqlDatabase db{QSqlDatabase::cloneDatabase(m_main, name)};

        m_lock.unlock();

        db.open();

        return db;
    }

    std::expected<QSqlDatabase, QSqlError> Manager::getConnection(void) {
        QSqlDatabase db{connect()};

        if (!db.open()) {
            qDebug() << "[Thread" << QThread::currentThreadId() << "] Failed to open DB:" << db.lastError().text();
            
            emit triggerLost(); 
            return db.lastError();
        }

        if (!isReady())
            emit triggerSuccess();

        qDebug() << "[Thread" << QThread::currentThreadId() << "] Connection authorized and cached.";
        return db;
    }

    Manager::operator bool(void) const {
        return *m_stateMachine.configuration().cbegin() == m_connected;
    }

    bool Manager::isReady(void) const {
        return bool(this);
    }

    void Manager::onConnectingEntered(void) {
        qDebug() << "[State Machine] Connecting to database master server...";

        QSqlDatabase db{connect()};

        if (db.open())
            emit triggerSuccess();
        else {
            qDebug() << "[State Machine] Master connection failed:" << db.lastError().text();
            emit triggerFailure();
        }
    }

    void Manager::onConnectedEntered(void) {
        qDebug() << "[State Machine] DATABASE READY. All threads unblocked.";
    }

    void Manager::onErrorEntered(void) {
        qDebug() << "[State Machine] Critical Error State. Reconnecting in 5 seconds...";
        
        QTimer::singleShot(5000, this, [this]() {
            emit triggerConnect();
        });
    }
}
