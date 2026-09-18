#pragma once

#include <QObject>
#include <QHttpServer>
#include <QJsonObject>
#include <QHttpServerResponse>
#include <QDateTime>
#include <QTcpServer>
#include <stdexcept>


class HttpServer final : public QObject {
    Q_OBJECT

private:
    QHttpServer * m_httpServer{nullptr};
    QTcpServer * m_tcpServer{nullptr};

public:
    explicit HttpServer(quint16 port = 0, QObject * parent = nullptr);

    ~HttpServer();

    explicit operator bool() const noexcept;

private:
    static QHttpServerResponse handlePing(const QHttpServerRequest & request);
};
