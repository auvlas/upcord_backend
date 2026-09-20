
namespace Database {
    namespace Models {
        User::User(qint64 id) : m_id{id} {

        }

        std::optional<std::pair<User, QString> User::loginUserName(
                QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginEmail(
                QString userName, QString password) {

        }

        std::optional<std::pair<User, QString> User::loginPhone(
                QString userName, QString password) {

        }

        std::pair<User, QString> User::create(QString visibleName,
                QString userName, QString password, QString firstName,
                QString secondName, QString fatherName,
                QString email, QString phone) {

        }

        std::optional<std::pair<User, QString>> User::login(
                QString UEP, QString password) {

        }

        std::pair<QList<Server>, QList<DirectMessage>>
                User::login(QString jwt) {

        }

        QJsonObject User::create(QJsonObject newUser) {

        }

        QJsonObject User::login(QJsonObject authorizationData) {

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
