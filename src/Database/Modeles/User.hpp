#pragma once

#include <QtTypes>
#include <QString>
#include <optional>
#include <utility>
#include <Database/DatabaseManager.hpp>


namespace Database {
    namespace Models {
        class User {
        private:
            Database db{};
            qint64 m_id{0};
            QString m_visibleName{};
            QString m_userName{};
            // QString m_hashPassword{};
            QString m_firstName{};
            QString m_secondName{};
            QString m_fatherName{};
            QString m_email{};
            QString m_phone{};
            // QList<QString> m_activeSessionJwt{};

            explicit User(Database db, qint64 id);

        public:
            static std::optional<std::pair<User, QString> loginUserName(
                    Database db, QString userName, QString password);

            static std::optional<std::pair<User, QString> loginEmail(
                    Database db, QString userName, QString password);

            static std::optional<std::pair<User, QString> loginPhone(
                    Database db, QString userName, QString password);

            static std::pair<User, QString> create(Database db,
                    QString visibleName, QString userName,
                    QString password, QString firstName,
                    QString secondName, QString fatherName,
                    QString email, QString phone);

            static std::optional<std::pair<User, QString>> login(
                    Database db, QString UEP, QString password);

            static std::pair<QList<Server>, QList<DirectMessage>> login(
                    Database db, QString jwt);

            static QJsonObject create(Database db, QJsonObject newUser);

            static QJsonObject login(Database db, QJsonObject authorizationData);

            QJsonObject getJson() const;
        };
    }
}
