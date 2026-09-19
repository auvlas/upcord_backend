#include <QObject>
#include <QString>
#include <QByteArray>
#include <QRandomGenerator>
#include <QHttpServerRequest>
#include <QtTypes>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QPasswordDigestor>
#include <QHttpHeaders>
#include <string>
#include <jwt-cpp/jwt.h>
#include <snowflake.hpp>

#include <HttpServer/Secret.hpp>


namespace HttpServer {
    Secret::Secret(QString domain, QString pathJwtSecret,
            QObject * parent) noexcept : QObject{parent},
        m_domain{domain}, m_pathJwtSecret{pathJwtSecret} {

        if (!exists()) {
            qInfo() << "Input passphrase: ";
            QTextStream in(stdin);
            QString passphrase = in.readLine();
    
            setJwtSecret(generateSecureJwtSecret(passphrase));

            qWarning() << "File for JWT secret: "
                    << m_pathJwtSecret << ", not found!";
            qDebug() << "Generate new JWT Secret.";
        }
    }

    qint64 Secret::verifyToken(const QHttpServerRequest & request) noexcept {
        QString tokenStr{extractJwtToken(request)};

        if (tokenStr.isEmpty()) return -1;

        try {
            std::string token = tokenStr.toStdString();
            jwt::decoded_jwt<jwt::traits::kazuho_picojson>
                decoded = jwt::decode(token);

            jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson>
                verifier = jwt::verify().allow_algorithm(
                    jwt::algorithm::hs256{
                        getJwtSecret().toStdString()
                    }
            ).with_issuer(m_domain.toStdString());

            verifier.verify(decoded);
            std::string userIdStr = decoded.get_payload_claim("user_id").as_string();
            return std::stoll(userIdStr);
        } catch (const std::exception &e) {
            qWarning() << "Warning: decode JWT token: \n\t" << tokenStr << "\n\t\t" << e.what();
            return -1;
        }
    }

    QString Secret::generateSecureJwtSecret(const QString &passphrase) noexcept {
        QByteArray dynamicSalt;
        dynamicSalt.resize(16); 
        
        QRandomGenerator *cryptoRandom = QRandomGenerator::system();
        cryptoRandom->fillRange(
            reinterpret_cast<quint32*>(dynamicSalt.data()), 
            dynamicSalt.size() / sizeof(quint32)
        );

        QByteArray derivedKey = QPasswordDigestor::deriveKeyPbkdf2(
            QCryptographicHash::Sha256, passphrase.toUtf8(), 
            dynamicSalt, 10000, 32
        );

        return derivedKey.toBase64();
    }

    QByteArray Secret::readFile(const QString &pathFile) noexcept {
        QFile file(pathFile);
        
        if (!file.open(QIODevice::ReadOnly)) {
            return QByteArray();
        }
        
        return file.readAll();
    }

    bool Secret::writeFile(const QString &pathFile, const QByteArray &data) noexcept {
        QFile file(pathFile);
        
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return false;
        }
        
        qint64 bytesWritten = file.write(data);
        
        return (bytesWritten == data.size());
    }

    bool Secret::exists() noexcept {
        QFileInfo fileInfo(m_pathJwtSecret);
        
        return fileInfo.exists() && (fileInfo.size() > 0);
    }

    QString Secret::getJwtSecret() noexcept {
        return readFile(m_pathJwtSecret);
    }

    bool Secret::setJwtSecret(QString jwtSecret) noexcept {
        return writeFile(m_pathJwtSecret, jwtSecret.toLocal8Bit());
    }

    QString Secret::extractJwtToken(const QHttpServerRequest & request) noexcept {
        for (const std::pair<QByteArray, QByteArray> & header
                : request.headers().toListOfPairs()) {
            if (header.first.toLower() == "authorization") {
                QString authHeader = QString::fromUtf8(header.second);
                
                if (authHeader.startsWith("Bearer ", Qt::CaseInsensitive)) {
                    return authHeader.mid(7).trimmed();
                }
            }
        }
        return QString{};
    }
}
