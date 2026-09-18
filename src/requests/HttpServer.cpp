#include <QObject>
#include <QHttpServer>
#include <QJsonObject>
#include <QHttpServerResponse>
#include <QDateTime>
#include <QTcpServer>
#include <QtTypes>
#include <stdexcept>
#include <requests/PortUnavaliableException.hpp>
#include <jwt-cpp/jwt.h>

#include <requests/HttpServer.hpp>


HttpServer::HttpServer(quint16 port, QObject * parent) : QObject{parent},
        m_httpServer{new QHttpServer{this}}, m_tcpServer{new QTcpServer(this)} {
    if (!m_tcpServer->listen(QHostAddress::Any, port)
            || !m_httpServer->bind(m_tcpServer)) {
        delete m_httpServer, delete m_tcpServer;
        m_httpServer = nullptr, m_tcpServer = nullptr;

        throw PortUnavaliableException();
    }

    m_httpServer->route("/ping", QHttpServerRequest::Method::Get, handlePing);
}

HttpServer::~HttpServer()
{
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
    }
}

HttpServer::operator bool() const noexcept {
    return m_httpServer && m_tcpServer;
}

QHttpServerResponse HttpServer::handlePing(const QHttpServerRequest & request) {
    Q_UNUSED(request);
    QJsonObject jsonResponse;
    jsonResponse["status"] = "pong";
    jsonResponse["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    return QHttpServerResponse(jsonResponse, QHttpServerResponse::StatusCode::Ok);
}
