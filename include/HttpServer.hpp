#pragma once

#include <QObject>
#include <QHttpServer>
#include <QHttpServerResponse>
#include <QDateTime>
#include <QTcpServer>
#include <Secret.hpp>
#include <Database/Manager.hpp>


class HttpServer final : public QObject {
    Q_OBJECT

private:
    Secret m_secret;
    QHttpServer m_httpServer{};
    QTcpServer m_tcpServer{};

public:
    explicit HttpServer(QString domain, QString pathJwtSecret,
            Database::DatabaseManager * database = nullptr, quint16 port = 0,
            QObject * parent = nullptr);

    ~HttpServer();

    explicit operator bool() const noexcept;

private slots:
    static QHttpServerResponse handlePing(
            const QHttpServerRequest & request);

    QHttpServerResponse handleStart(
        const QHttpServerRequest &request);

    QHttpServerResponse handleGetServers(
            const QHttpServerRequest &request);

    QHttpServerResponse handleGetDirectMessages(
            const QHttpServerRequest &request);
};
