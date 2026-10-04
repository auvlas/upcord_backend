#pragma once

#include <QObject>
#include <QHttpServer>
#include <QHttpServerResponse>
#include <QDateTime>
#include <QTcpServer>
#include <HttpServer/Secret.hpp>


namespace HttpServer {
    class HttpServer final : public QObject {
        Q_OBJECT

    private:
        Secret m_secret;
        QHttpServer m_httpServer{};
        QTcpServer m_tcpServer{};

    public:
        explicit HttpServer(QString domain, QString pathJwtSecret,
                quint16 port = 0, QObject * parent = nullptr);

        ~HttpServer();

        explicit operator bool() const noexcept;

    private:
        static QHttpServerResponse handlePing(
                const QHttpServerRequest & request);

        static QHttpServerResponse handleGetServers(
                const QHttpServerRequest &request);
        static QHttpServerResponse handleGetDirectMessages(
                const QHttpServerRequest &request);
    };
}
