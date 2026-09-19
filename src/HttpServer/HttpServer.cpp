#include <QObject>
#include <QHttpServer>
#include <QJsonObject>
#include <QHttpServerResponse>
#include <QDateTime>
#include <QTcpServer>
#include <QtTypes>
#include <QString>
#include <QByteArray>
#include <stdexcept>
#include <HttpServer/Exception.hpp>
#include <HttpServer/Secret.hpp>
#include <jwt-cpp/jwt.h>

#include <HttpServer/HttpServer.hpp>


namespace HttpServer {
    HttpServer::HttpServer(QString pathJwtSecret,
            QString domain, quint16 port, QObject * parent)
        : QObject{parent}, m_secret{pathJwtSecret, domain} {

        if (!m_tcpServer.listen(QHostAddress::Any, port)
                || !m_httpServer.bind(&m_tcpServer)) {

            throw Exception::PortUnavaliableException();
        }

        m_httpServer.route("/ping", QHttpServerRequest::Method::Get, handlePing);
        m_httpServer.route("/start", QHttpServerRequest::Method::Get, handleStart);
        m_httpServer.route("/dms", QHttpServerRequest::Method::Get, handleStart);
        m_httpServer.route("/servers", QHttpServerRequest::Method::Get, handleStart);
    }

    HttpServer::~HttpServer() {
        if (m_tcpServer.isListening()) {
            m_tcpServer.close();
        }
    }

    QHttpServerResponse HttpServer::handlePing(const QHttpServerRequest & request) {
        Q_UNUSED(request);
        QJsonObject jsonResponse{};
        jsonResponse["status"] = "pong";
        jsonResponse["timestamp"] = QDateTime::currentMSecsSinceEpoch();
        return QHttpServerResponse(jsonResponse, QHttpServerResponse::StatusCode::Ok);
    }

    QHttpServerResponse HttpServer::handleStart(
            const QHttpServerRequest &request) {
        qint64 userId = m_secret.verifyToken(request);
        if (userId == -1) {
            return QHttpServerResponse(QHttpServerResponse::StatusCode::Unauthorized);
        }

        QJsonArray servers;
        QJsonObject server1;
        server1["id"] = 101;
        server1["name"] = "Upcord General";
        servers.append(server1);

        QJsonObject responseJson;
        responseJson["servers"] = servers;

        QHttpServerResponse response(responseJson);
        response.setHeader("Access-Control-Allow-Origin", "*");
        return response;
    }

    QHttpServerResponse HttpServer::handleGetServers(
            const QHttpServerRequest &request) {
        qint64 userId = m_secret.verifyToken(request);
        if (userId == -1) {
            return QHttpServerResponse(QHttpServerResponse::StatusCode::Unauthorized);
        }

        QJsonArray servers;
        QJsonObject server1;
        server1["id"] = 101;
        server1["name"] = "Upcord General";
        servers.append(server1);

        QJsonObject responseJson;
        responseJson["servers"] = servers;

        QHttpServerResponse response(responseJson);
        response.setHeader("Access-Control-Allow-Origin", "*");
        return response;
    }

    QHttpServerResponse HttpServer::handleGetDirectMessages(
            const QHttpServerRequest &request) {
        qint64 userId = m_secret.verifyToken(request);

        if (userId == -1) {
            return QHttpServerResponse(QHttpServerResponse::StatusCode::Unauthorized);
        }

        QJsonArray dms;
        QJsonObject chat1;
        chat1["chat_id"] = 555;
        chat1["with_user"] = "Alex";
        dms.append(chat1);

        QJsonObject responseJson;
        responseJson["direct_messages"] = dms;

        QHttpServerResponse response(responseJson);
        response.setHeader("Access-Control-Allow-Origin", "*");
        return response;
    }
}
