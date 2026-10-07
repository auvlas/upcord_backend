#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QRandomGenerator>
#include <QHttpServerRequest>
#include <QtTypes>


namespace HttpServer {
    class Secret final : public QObject {
        Q_OBJECT

    private:
        QString m_domain{};
        QString m_pathJwtSecret{};
        QString m_jwtSecret{};

    public:
        explicit Secret(QString m_domain, QString pathJwtSecret,
                QObject * parent = nullptr) noexcept;

        qint64 verifyToken(const QHttpServerRequest & request) noexcept;

    private:
        QString generateSecureJwtSecret(const QString &passphrase) noexcept;

        static QByteArray readFile(const QString &pathFile) noexcept;

        static bool writeFile(const QString &pathFile,
                const QByteArray &data) noexcept;

        bool exists() noexcept;

        QString getJwtSecret() noexcept;

        bool setJwtSecret(QString jwtSecret) noexcept;

        QString extractJwtToken(const QHttpServerRequest & request) noexcept;
    };
}
