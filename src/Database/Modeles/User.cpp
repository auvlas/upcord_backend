#pragma once

#include <QtTypes>
#include <QString>
#include <optional>
#include <utility>
#include "Database/Database.hpp"


namespace Database {
    namespace Models {
        User::User(Database db, qint64 id) : m_id{id} {

        }

        std::optional<std::pair<User, QString> User::loginUserName(
                Database db, QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginEmail(
                Database db, QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginPhone(
                Database db, QString userName, QString password) {

        }

        std::pair<User, QString> User::create(Database db,
                QString visibleName, QString userName,
                QString password, QString firstName,
                QString secondName, QString fatherName,
                QString email, QString phone) {

        }

        std::optional<std::pair<User, QString>> User::login(
                Database db, QString UEP, QString password) {

        }

        std::pair<QList<Server>, QList<DirectMessage>>
                User::login(Database db, QString jwt) {

        }

        QJsonObject User::create(Database db, QJsonObject newUser) {

        }

        QJsonObject User::login(Database db, QJsonObject authorizationData) {

        }

        QJsonObject User::getJson() {
            QJsonObject user;
            user["id"] = m_id;
            
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
