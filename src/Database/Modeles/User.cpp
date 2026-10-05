#pragma once

#include <QtTypes>
#include <QString>
#include <optional>
#include <utility>
#include <Database/DatabaseManager.hpp>


namespace Database {
    namespace Models {
        User::User(DatabaseManager db, qint64 id) : m_id{id} {

        }

        std::optional<std::pair<User, QString> User::loginUserName(
                DatabaseManager db, QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginEmail(
                DatabaseManager db, QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginPhone(
                DatabaseManager db, QString userName, QString password) {

        }

        std::pair<User, QString> User::create(DatabaseManager db,
                QString visibleName, QString userName,
                QString password, QString firstName,
                QString secondName, QString fatherName,
                QString email, QString phone) {

        }

        std::optional<std::pair<User, QString>> User::login(
                DatabaseManager db, QString UEP, QString password) {

        }

        std::pair<QList<Server>, QList<DirectMessage>>
                User::login(DatabaseManager db, QString jwt) {

        }

        QJsonObject User::create(DatabaseManager db, QJsonObject newUser) {

        }

        QJsonObject User::login(DatabaseManager db, QJsonObject authorizationData) {

        }

        QJsonObject User::getJson() {
            QJsonObject user;
            user["visibleName"] = m_visibleName;
            user["userName"] = m_userName;
            user["firstName"] = m_firstName;
            user["secondName"] = m_secondName;
            user["fatherName"] = m_fatherName;
            user["email"] = m_email;
            user["phone"] = m_phone;

            return user;
        }
    }
}
