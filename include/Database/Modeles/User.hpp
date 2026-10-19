#pragma once

#include <QtTypes>
#include <QString>
#include <optional>
#include <utility>
#include <Database/Models/Chat.hpp>
#include <Database/Models/Server.hpp>
#include <Database/Manager.hpp>


namespace Database {
    namespace Models {
        class User {
        private:
            Manager db;
            QString m_visibleName;
            QString m_userName;
            // QString m_hashPassword;
            QString m_firstName;
            QString m_secondName;
            QString m_fatherName;
            QString m_email;
            QString m_phone;
            // QList<QString> m_activeSessionJwt;

            explicit User(Manager db, qint64 id);

        public:
            static std::optional<std::pair<User, QString>> loginUserName(
                    Manager db, QString userName, QString password);

            static std::optional<std::pair<User, QString>> loginEmail(
                    Manager db, QString email, QString password);

            static std::optional<std::pair<User, QString>> loginPhone(
                    Manager db, QString phone, QString password);

            static std::pair<User, QString> create(Manager db,
                    QString visibleName, QString userName,
                    QString password, QString firstName,
                    QString secondName, QString fatherName,
                    QString email, QString phone);

            static std::optional<std::pair<User, QString>> login(
                    Manager db, QString UEP, QString password);

            static std::pair<QList<Server>, QList<Chat>> login(
                    Manager db, QString jwt);

            static QJsonObject create(Manager db, QJsonObject newUser);

            static QJsonObject login(Manager db, QJsonObject authorizationData);

            QJsonObject getJson() const;
        };
    }
}
