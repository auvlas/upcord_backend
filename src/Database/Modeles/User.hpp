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
            DatabaseManager db{};
            QString m_visibleName{};
            QString m_userName{};
            // QString m_hashPassword{};
            QString m_firstName{};
            QString m_secondName{};
            QString m_fatherName{};
            QString m_email{};
            QString m_phone{};
            // QList<QString> m_activeSessionJwt{};

            explicit User(DatabaseManager db, qint64 id);

        public:
            static std::optional<std::pair<User, QString> loginUserName(
                    DatabaseManager db, QString userName, QString password);

            static std::optional<std::pair<User, QString> loginEmail(
                    DatabaseManager db, QString userName, QString password);

            static std::optional<std::pair<User, QString> loginPhone(
                    DatabaseManager db, QString userName, QString password);

            static std::pair<User, QString> create(DatabaseManager db,
                    QString visibleName, QString userName,
                    QString password, QString firstName,
                    QString secondName, QString fatherName,
                    QString email, QString phone);

            static std::optional<std::pair<User, QString>> login(
                    DatabaseManager db, QString UEP, QString password);

            static std::pair<QList<Server>, QList<DirectMessage>> login(
                    DatabaseManager db, QString jwt);

            static QJsonObject create(DatabaseManager db, QJsonObject newUser);

            static QJsonObject login(DatabaseManager db, QJsonObject authorizationData);

            QJsonObject getJson() const;
        };
    }
}
